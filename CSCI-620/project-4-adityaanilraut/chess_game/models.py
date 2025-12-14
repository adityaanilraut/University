from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone
import chess


class Game(models.Model):
    STATUS_CHOICES = [
        ('active', 'Active'),
        ('completed', 'Completed'),
    ]
    
    OUTCOME_CHOICES = [
        ('win', 'Win'),
        ('loss', 'Loss'),
        ('resignation', 'Resignation'),
        ('checkmate', 'Checkmate'),
        ('stalemate', 'Stalemate'),
    ]
    
    white_player = models.ForeignKey(User, on_delete=models.CASCADE, related_name='games_as_white')
    black_player = models.ForeignKey(User, on_delete=models.CASCADE, related_name='games_as_black')
    board_state = models.TextField(default='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')  # Starting FEN
    current_turn = models.CharField(max_length=5, default='white', choices=[('white', 'White'), ('black', 'Black')])
    status = models.CharField(max_length=10, choices=STATUS_CHOICES, default='active')
    winner = models.ForeignKey(User, on_delete=models.CASCADE, null=True, blank=True, related_name='games_won')
    outcome = models.CharField(max_length=15, choices=OUTCOME_CHOICES, null=True, blank=True)
    created_at = models.DateTimeField(default=timezone.now)
    updated_at = models.DateTimeField(default=timezone.now)
    
    def __str__(self):
        return f"Game {self.id}: {self.white_player.username} vs {self.black_player.username}"
    
    def save(self, *args, **kwargs):
        self.updated_at = timezone.now()
        super().save(*args, **kwargs)
    
    def get_board(self):
        """Return a python-chess Board object from the FEN string"""
        return chess.Board(self.board_state)
    
    def update_board_state(self, new_fen):
        """Update the board state and check for game end conditions"""
        self.board_state = new_fen
        board = chess.Board(new_fen)
        
        if board.is_checkmate():
            self.status = 'completed'
            self.outcome = 'checkmate'
            # Winner is the player whose turn it is NOT (since they got checkmated)
            self.winner = self.black_player if self.current_turn == 'white' else self.white_player
        elif board.is_stalemate():
            self.status = 'completed'
            self.outcome = 'stalemate'
            self.winner = None  # Draw
        elif board.is_game_over():
            self.status = 'completed'
            self.outcome = 'stalemate'  # Other game over conditions
            self.winner = None
        
        self.save()


class Challenge(models.Model):
    STATUS_CHOICES = [
        ('pending', 'Pending'),
        ('accepted', 'Accepted'),
        ('declined', 'Declined'),
    ]
    
    challenger = models.ForeignKey(User, on_delete=models.CASCADE, related_name='challenges_made')
    opponent = models.ForeignKey(User, on_delete=models.CASCADE, related_name='challenges_received')
    status = models.CharField(max_length=10, choices=STATUS_CHOICES, default='pending')
    created_at = models.DateTimeField(default=timezone.now)
    
    def __str__(self):
        return f"{self.challenger.username} challenges {self.opponent.username} - {self.status}"
    
    class Meta:
        # Note: Duplicate pending challenges are handled in consumers.py send_challenge()
        # We don't use unique_together here to allow multiple accepted/declined challenges over time
        pass


class Move(models.Model):
    game = models.ForeignKey(Game, on_delete=models.CASCADE, related_name='moves')
    player = models.ForeignKey(User, on_delete=models.CASCADE)
    move_notation = models.CharField(max_length=10)  # UCI format (e.g., 'e2e4')
    board_state_after = models.TextField()  # FEN notation after the move
    move_number = models.IntegerField()
    created_at = models.DateTimeField(default=timezone.now)
    
    def __str__(self):
        return f"Move {self.move_number}: {self.move_notation} by {self.player.username}"
    
    class Meta:
        ordering = ['move_number']