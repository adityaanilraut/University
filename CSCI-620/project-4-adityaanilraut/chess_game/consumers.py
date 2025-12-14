"""
WebSocket consumers for real-time chess game communication
"""
import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from django.contrib.auth import get_user_model
from django.db.models import Q

from .models import Game, Challenge

User = get_user_model()


class GameConsumer(AsyncWebsocketConsumer):
    """WebSocket consumer for individual game rooms"""
    
    async def connect(self):
        self.game_id = self.scope['url_route']['kwargs']['game_id']
        self.room_group_name = f'game_{self.game_id}'
        
        # Check if user is authenticated
        if not self.scope['user'].is_authenticated:
            await self.close()
            return
        
        # Check if user is part of this game
        game = await self.get_game(self.game_id)
        if not game:
            await self.close()
            return
        
        user = self.scope['user']
        if game.white_player_id != user.id and game.black_player_id != user.id:
            await self.close()
            return
        
        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        
        await self.accept()
        
        # Send current game state to the newly connected client
        game_state = await self.get_game_state(game, user)
        await self.send(text_data=json.dumps({
            'type': 'game_state',
            'data': game_state
        }))
    
    async def disconnect(self, close_code):
        # Only process disconnect if connection was successful
        if not hasattr(self, 'room_group_name'):
            return
            
        # Leave room group
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )
    
    async def receive(self, text_data):
        """Handle messages received from WebSocket"""
        data = json.loads(text_data)
        message_type = data.get('type')
        
        if message_type == 'new_move':
            # Handle new move
            await self.handle_new_move(data)
        elif message_type == 'game_action':
            # Handle game actions like resignation
            await self.handle_game_action(data)
    
    async def handle_new_move(self, data):
        """Handle a new move from a player"""
        from_square = data.get('from_square')
        to_square = data.get('to_square')
        
        if not from_square or not to_square:
            await self.send(text_data=json.dumps({
                'type': 'error',
                'message': 'Invalid move data'
            }))
            return
        
        # Process move and update game state
        result = await self.make_move(self.game_id, self.scope['user'], from_square, to_square)
        
        if result.get('success'):
            # Broadcast updated game state to all players in the room
            game = await self.get_game(self.game_id)
            white_player = await database_sync_to_async(User.objects.get)(id=game.white_player_id)
            black_player = await database_sync_to_async(User.objects.get)(id=game.black_player_id)
            
            # Send to white player
            white_game_state = await self.get_game_state(game, white_player)
            # Send to black player
            black_game_state = await self.get_game_state(game, black_player)
            
            # Broadcast to group
            await self.channel_layer.group_send(
                self.room_group_name,
                {
                    'type': 'game_state_update',
                    'white_state': white_game_state,
                    'black_state': black_game_state,
                }
            )
        else:
            # Send error to the player who made the move
            await self.send(text_data=json.dumps({
                'type': 'error',
                'message': result.get('error', 'Invalid move')
            }))
    
    async def handle_game_action(self, data):
        """Handle game actions like resignation"""
        action = data.get('action')
        
        if action == 'resign':
            result = await self.resign_game(self.game_id, self.scope['user'])
            
            if result.get('success'):
                game = await self.get_game(self.game_id)
                white_player = await database_sync_to_async(User.objects.get)(id=game.white_player_id)
                black_player = await database_sync_to_async(User.objects.get)(id=game.black_player_id)
                
                white_game_state = await self.get_game_state(game, white_player)
                black_game_state = await self.get_game_state(game, black_player)
                
                await self.channel_layer.group_send(
                    self.room_group_name,
                    {
                        'type': 'game_state_update',
                        'white_state': white_game_state,
                        'black_state': black_game_state,
                    }
                )
    
    async def game_state_update(self, event):
        """Send game state update to WebSocket"""
        # Determine if current user is white or black and send appropriate state
        user = self.scope['user']
        game = await self.get_game(self.game_id)
        
        if game.white_player_id == user.id:
            game_state = event['white_state']
        else:
            game_state = event['black_state']
        
        await self.send(text_data=json.dumps({
            'type': 'game_state',
            'data': game_state
        }))
    
    @database_sync_to_async
    def get_game(self, game_id):
        """Get game object"""
        try:
            return Game.objects.get(id=game_id)
        except Game.DoesNotExist:
            return None
    
    @database_sync_to_async
    def get_game_state(self, game, user):
        """Get current game state for a user"""
        is_white_player = (game.white_player_id == user.id)
        is_current_turn = (
            (is_white_player and game.current_turn == 'white') or
            (not is_white_player and game.current_turn == 'black')
        )
        
        return {
            'game_id': game.id,
            'status': game.status,
            'current_turn': game.current_turn,
            'is_current_turn': is_current_turn,
            'outcome': game.outcome,
            'winner': game.winner.username if game.winner else None,
            'board_state': game.board_state,
        }
    
    @database_sync_to_async
    def make_move(self, game_id, user, from_square, to_square):
        """Make a move on the board"""
        import chess
        
        try:
            game = Game.objects.get(id=game_id)
            
            # Check if it's the user's turn
            is_white = (game.white_player_id == user.id)
            if (is_white and game.current_turn != 'white') or (not is_white and game.current_turn != 'black'):
                return {'success': False, 'error': 'Not your turn'}
            
            if game.status != 'active':
                return {'success': False, 'error': 'Game is not active'}
            
            # Validate and make move
            board = game.get_board()
            from_square_uci = chess.parse_square(from_square)
            to_square_uci = chess.parse_square(to_square)
            move = chess.Move(from_square_uci, to_square_uci)
            
            if move in board.legal_moves:
                board.push(move)
                
                # Save move to database
                from .models import Move
                Move.objects.create(
                    game=game,
                    player=user,
                    move_notation=f"{from_square}{to_square}",
                    board_state_after=board.fen(),
                    move_number=game.moves.count() + 1
                )
                
                # Update game state
                game.current_turn = 'black' if game.current_turn == 'white' else 'white'
                game.update_board_state(board.fen())
                
                return {'success': True, 'message': 'Move made successfully'}
            else:
                return {'success': False, 'error': 'Invalid move'}
                
        except (ValueError, IndexError, Game.DoesNotExist) as e:
            return {'success': False, 'error': 'Invalid move format'}
    
    @database_sync_to_async
    def resign_game(self, game_id, user):
        """Handle game resignation"""
        try:
            game = Game.objects.get(id=game_id)
            
            if game.status != 'active':
                return {'success': False, 'error': 'Game is not active'}
            
            # Set game as completed
            game.status = 'completed'
            game.outcome = 'resignation'
            game.winner = game.black_player if game.white_player_id == user.id else game.white_player
            game.save()
            
            return {'success': True, 'message': 'Game resigned successfully'}
        except Game.DoesNotExist:
            return {'success': False, 'error': 'Game not found'}


class LobbyConsumer(AsyncWebsocketConsumer):
    """WebSocket consumer for lobby updates (available players, challenges)"""
    
    async def connect(self):
        # Check if user is authenticated
        if not self.scope['user'].is_authenticated:
            await self.close()
            return
        
        user = self.scope['user']
        self.user_group_name = f'user_{user.id}'
        self.lobby_group_name = 'lobby'
        
        # Join user-specific group
        await self.channel_layer.group_add(
            self.user_group_name,
            self.channel_name
        )
        
        # Join global lobby group
        await self.channel_layer.group_add(
            self.lobby_group_name,
            self.channel_name
        )
        
        await self.accept()
        
        # Send initial lobby data
        lobby_data = await self.get_lobby_data(user)
        await self.send(text_data=json.dumps({
            'type': 'lobby_data',
            'data': lobby_data
        }))
        
        # Notify all other users in lobby that someone joined
        await self.channel_layer.group_send(
            self.lobby_group_name,
            {
                'type': 'lobby_update',
            }
        )
    
    async def disconnect(self, close_code):
        # Only process disconnect if user was successfully connected
        if not hasattr(self, 'user_group_name') or not hasattr(self, 'lobby_group_name'):
            return
        
        # Leave user-specific group
        await self.channel_layer.group_discard(
            self.user_group_name,
            self.channel_name
        )
        
        # Leave lobby group
        await self.channel_layer.group_discard(
            self.lobby_group_name,
            self.channel_name
        )
        
        # Notify all other users in lobby that someone left
        await self.channel_layer.group_send(
            self.lobby_group_name,
            {
                'type': 'lobby_update',
            }
        )
    
    async def receive(self, text_data):
        """Handle messages received from WebSocket"""
        data = json.loads(text_data)
        message_type = data.get('type')
        
        if message_type == 'send_challenge':
            await self.handle_send_challenge(data)
        elif message_type == 'respond_challenge':
            await self.handle_respond_challenge(data)
        elif message_type == 'request_lobby_update':
            lobby_data = await self.get_lobby_data(self.scope['user'])
            await self.send(text_data=json.dumps({
                'type': 'lobby_data',
                'data': lobby_data
            }))
    
    async def handle_send_challenge(self, data):
        """Handle sending a challenge to another player"""
        opponent_id = data.get('opponent_id')
        
        result = await self.send_challenge_to_player(self.scope['user'], opponent_id)
        
        if result.get('success'):
            # Notify the challenging user
            await self.send(text_data=json.dumps({
                'type': 'challenge_sent',
                'message': 'Challenge sent!'
            }))
            
            # Notify the opponent and update lobby for all users
            await self.channel_layer.group_send(
                self.lobby_group_name,
                {
                    'type': 'lobby_update',
                }
            )
        else:
            await self.send(text_data=json.dumps({
                'type': 'error',
                'message': result.get('error', 'Failed to send challenge')
            }))
    
    async def handle_respond_challenge(self, data):
        """Handle responding to a challenge"""
        challenge_id = data.get('challenge_id')
        response = data.get('response')  # 'accept' or 'decline'
        
        result = await self.respond_to_challenge(challenge_id, response, self.scope['user'])
        
        if result.get('success'):
            if response == 'accept' and result.get('game_id'):
                # Notify both players of new game
                challenger_id = result.get('challenger_id')
                
                # Update lobby for both players
                await self.channel_layer.group_send(
                    self.user_group_name,
                    {
                        'type': 'new_game',
                        'game_id': result.get('game_id')
                    }
                )
                
                await self.channel_layer.group_send(
                    f'user_{challenger_id}',
                    {
                        'type': 'new_game',
                        'game_id': result.get('game_id')
                    }
                )
                
                # Notify entire lobby that players are now in a game
                await self.channel_layer.group_send(
                    self.lobby_group_name,
                    {
                        'type': 'lobby_update',
                    }
                )
            else:
                # Notify of challenge response
                await self.send(text_data=json.dumps({
                    'type': 'challenge_response',
                    'message': result.get('message', 'Challenge response sent')
                }))
                
                # Update lobby for all users
                await self.channel_layer.group_send(
                    self.lobby_group_name,
                    {
                        'type': 'lobby_update',
                    }
                )
        else:
            await self.send(text_data=json.dumps({
                'type': 'error',
                'message': result.get('error', 'Failed to respond to challenge')
            }))
    
    async def lobby_update(self, event):
        """Handle lobby update event"""
        lobby_data = await self.get_lobby_data(self.scope['user'])
        await self.send(text_data=json.dumps({
            'type': 'lobby_data',
            'data': lobby_data
        }))
    
    async def new_game(self, event):
        """Handle new game event"""
        await self.send(text_data=json.dumps({
            'type': 'new_game',
            'game_id': event['game_id']
        }))
    
    @database_sync_to_async
    def get_lobby_data(self, user):
        """Get available players and challenges for lobby"""
        from .utils import get_available_players
        
        available_players = get_available_players(user)
        players_data = [{'id': player.id, 'username': player.username} for player in available_players]
        
        # Get pending challenges
        pending_challenges = Challenge.objects.filter(opponent=user, status='pending')
        challenges_data = [
            {
                'id': challenge.id,
                'challenger': {
                    'id': challenge.challenger.id,
                    'username': challenge.challenger.username
                },
                'created_at': challenge.created_at.isoformat()
            }
            for challenge in pending_challenges
        ]
        
        # Get my challenges
        my_challenges = Challenge.objects.filter(challenger=user, status='pending')
        my_challenges_data = [
            {
                'id': challenge.id,
                'opponent': {
                    'id': challenge.opponent.id,
                    'username': challenge.opponent.username
                },
                'status': challenge.status
            }
            for challenge in my_challenges
        ]
        
        return {
            'available_players': players_data,
            'pending_challenges': challenges_data,
            'my_challenges': my_challenges_data
        }
    
    @database_sync_to_async
    def send_challenge_to_player(self, user, opponent_id):
        """Send a challenge to another player"""
        try:
            opponent = User.objects.get(id=opponent_id)
        except User.DoesNotExist:
            return {'success': False, 'error': 'Opponent not found'}
        
        # Check if challenge already exists
        existing_challenge = Challenge.objects.filter(
            challenger=user,
            opponent=opponent,
            status='pending'
        ).first()
        
        if existing_challenge:
            return {'success': False, 'error': 'Challenge already sent'}
        
        # Create new challenge
        challenge = Challenge.objects.create(
            challenger=user,
            opponent=opponent,
            status='pending'
        )
        
        return {'success': True, 'challenge_id': challenge.id}
    
    @database_sync_to_async
    def respond_to_challenge(self, challenge_id, response, user):
        """Accept or decline a challenge"""
        try:
            challenge = Challenge.objects.get(id=challenge_id, opponent=user)
        except Challenge.DoesNotExist:
            return {'success': False, 'error': 'Challenge not found'}
        
        if challenge.status != 'pending':
            return {'success': False, 'error': 'Challenge already responded to'}
        
        if response == 'accept':
            challenge.status = 'accepted'
            challenge.save()
            
            # Create new game
            game = Game.objects.create(
                white_player=challenge.challenger,
                black_player=challenge.opponent,
                current_turn='white'
            )
            
            return {
                'success': True,
                'message': 'Challenge accepted',
                'game_id': game.id,
                'challenger_id': challenge.challenger.id
            }
        elif response == 'decline':
            challenge.status = 'declined'
            challenge.save()
            return {'success': True, 'message': 'Challenge declined'}
        else:
            return {'success': False, 'error': 'Invalid response'}

