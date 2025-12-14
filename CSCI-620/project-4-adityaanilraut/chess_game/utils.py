from django.contrib.sessions.models import Session
from django.contrib.auth.models import User
from django.utils.timezone import now
import chess


def get_logged_in_users_excluding_current(user):
    """
    Get all currently logged-in users excluding the current user.
    Based on the example code provided in the requirements.
    """
    # Get all non-expired sessions
    active_sessions = Session.objects.filter(expire_date__gte=now())
    user_ids = []
    
    for session in active_sessions:
        session_data = session.get_decoded()
        user_id = session_data.get('_auth_user_id')
        if user_id:
            user_ids.append(user_id)
    
    # Convert IDs to unique set and exclude the current user
    logged_in_users = User.objects.filter(id__in=set(user_ids)).exclude(id=user.id)
    return logged_in_users


def get_available_players(user):
    """
    Get players that are logged in and not currently in an active game.
    """
    from .models import Game
    
    logged_in_users = get_logged_in_users_excluding_current(user)
    active_game_users = set()
    
    # Get users who are currently in active games
    active_games = Game.objects.filter(status='active')
    for game in active_games:
        active_game_users.add(game.white_player.id)
        active_game_users.add(game.black_player.id)
    
    # Filter out users with active games
    available_users = logged_in_users.exclude(id__in=active_game_users)
    return available_users


def board_to_dict(board):
    """
    Convert a python-chess Board object to a dictionary for template rendering.
    Returns a list of dictionaries, each representing a row.
    """
    board_dict = []
    
    # Generate 8 rows (ranks 8 to 1)
    for rank in range(7, -1, -1):
        row_dict = {}
        for file in range(8):
            square = chess.square(file, rank)
            piece = board.piece_at(square)
            square_name = chess.square_name(square)
            
            if piece:
                # Use HTML entity for chess pieces
                piece_unicode = piece.unicode_symbol()
                row_dict[square_name] = piece_unicode
            else:
                row_dict[square_name] = '&nbsp;'
        
        board_dict.append(row_dict)
    
    return board_dict


def board_to_dict_flipped(board):
    """
    Convert a python-chess Board object to a dictionary for template rendering,
    flipped for black player perspective.
    """
    board_dict = []
    
    # Generate 8 rows (ranks 1 to 8) - flipped
    for rank in range(8):
        row_dict = {}
        for file in range(7, -1, -1):  # Reverse files too
            square = chess.square(file, rank)
            piece = board.piece_at(square)
            # Convert to flipped square name
            flipped_file = 7 - file
            flipped_rank = 7 - rank
            flipped_square = chess.square(flipped_file, flipped_rank)
            square_name = chess.square_name(flipped_square)
            
            if piece:
                # Use HTML entity for chess pieces
                piece_unicode = piece.unicode_symbol()
                row_dict[square_name] = piece_unicode
            else:
                row_dict[square_name] = '&nbsp;'
        
        board_dict.append(row_dict)
    
    return board_dict


def validate_move_notation(move_notation):
    """
    Validate that the move notation is in correct format (e.g., "e2", "e4").
    Returns True if valid, False otherwise.
    """
    if len(move_notation) != 2:
        return False
    
    file_letter = move_notation[0].lower()
    rank_number = move_notation[1]
    
    # Check if file is a-h and rank is 1-8
    if file_letter not in 'abcdefgh' or rank_number not in '12345678':
        return False
    
    return True


def get_user_game_history(user):
    """
    Get the game history for a user, showing opponent, move count, and outcome.
    """
    from .models import Game
    from django.db import models
    
    # Get games where user was either white or black player
    games = Game.objects.filter(
        models.Q(white_player=user) | models.Q(black_player=user),
        status='completed'
    ).order_by('-created_at')
    
    history = []
    for game in games:
        # Determine opponent
        opponent = game.black_player if game.white_player == user else game.white_player
        
        # Get move count
        move_count = game.moves.count()
        
        # Determine outcome from user's perspective
        if game.winner == user:
            outcome = 'Win'
        elif game.winner is None:
            outcome = 'Draw'
        else:
            outcome = 'Loss'
        
        history.append({
            'opponent': opponent.username,
            'move_count': move_count,
            'outcome': outcome,
            'game': game
        })
    
    return history
