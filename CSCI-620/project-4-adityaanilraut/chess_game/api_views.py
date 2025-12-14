from rest_framework import status
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated, AllowAny
from rest_framework.response import Response
from django.contrib.auth import authenticate, login, logout
from django.middleware.csrf import get_token
from django.views.decorators.csrf import ensure_csrf_cookie
from django.db.models import Q

from .models import Game, Challenge
from .serializers import (
    UserSerializer,
    UserRegistrationSerializer,
    GameSerializer,
    GameListSerializer,
    ChallengeSerializer,
    LobbyDataSerializer,
    GameHistorySerializer,
)
from .utils import get_available_players, get_user_game_history


@api_view(['GET'])
@permission_classes([AllowAny])
@ensure_csrf_cookie
def get_csrf_token(request):
    """Get CSRF token for the frontend"""
    return Response({'csrfToken': get_token(request)})


@api_view(['GET'])
@permission_classes([AllowAny])
def get_current_user(request):
    """Get the currently authenticated user"""
    if request.user.is_authenticated:
        serializer = UserSerializer(request.user)
        return Response({
            'isAuthenticated': True,
            'user': serializer.data
        })
    return Response({
        'isAuthenticated': False,
        'user': None
    })


@api_view(['POST'])
@permission_classes([AllowAny])
def login_view(request):
    """Handle user login"""
    username = request.data.get('username')
    password = request.data.get('password')

    if not username or not password:
        return Response(
            {'error': 'Username and password are required'},
            status=status.HTTP_400_BAD_REQUEST
        )

    user = authenticate(request, username=username, password=password)
    if user is not None:
        login(request, user)
        serializer = UserSerializer(user)
        return Response({
            'message': 'Login successful',
            'user': serializer.data
        })
    else:
        return Response(
            {'error': 'Invalid username or password'},
            status=status.HTTP_401_UNAUTHORIZED
        )


@api_view(['POST'])
@permission_classes([AllowAny])
def register_view(request):
    """Handle user registration"""
    serializer = UserRegistrationSerializer(data=request.data)
    if serializer.is_valid():
        user = serializer.save()
        login(request, user)
        user_serializer = UserSerializer(user)
        return Response({
            'message': 'Registration successful',
            'user': user_serializer.data
        }, status=status.HTTP_201_CREATED)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['POST'])
@permission_classes([IsAuthenticated])
def logout_view(request):
    """Handle user logout"""
    logout(request)
    return Response({'message': 'Logout successful'})


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def lobby_view(request):
    """Get lobby data: available players, pending challenges, my challenges"""
    user = request.user
    
    # Get available players
    available_players = get_available_players(user)
    
    # Get pending challenges (challenges received by current user)
    pending_challenges = Challenge.objects.filter(
        opponent=user,
        status='pending'
    )
    
    # Get challenges made by current user
    my_challenges = Challenge.objects.filter(
        challenger=user,
        status='pending'
    )
    
    # Check for active game
    active_game = Game.objects.filter(
        Q(white_player=user) | Q(black_player=user),
        status='active'
    ).first()
    
    data = {
        'available_players': UserSerializer(available_players, many=True).data,
        'pending_challenges': ChallengeSerializer(pending_challenges, many=True).data,
        'my_challenges': ChallengeSerializer(my_challenges, many=True).data,
        'active_game_id': active_game.id if active_game else None,
    }
    
    return Response(data)


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def game_detail_view(request, game_id):
    """Get details of a specific game"""
    try:
        game = Game.objects.get(id=game_id)
    except Game.DoesNotExist:
        return Response(
            {'error': 'Game not found'},
            status=status.HTTP_404_NOT_FOUND
        )
    
    # Check if user is part of this game
    user = request.user
    if game.white_player != user and game.black_player != user:
        return Response(
            {'error': 'You are not authorized to view this game'},
            status=status.HTTP_403_FORBIDDEN
        )
    
    # Determine player's color and turn status
    is_white_player = (game.white_player == user)
    is_current_turn = (
        (is_white_player and game.current_turn == 'white') or
        (not is_white_player and game.current_turn == 'black')
    )
    
    serializer = GameSerializer(game)
    data = serializer.data
    data['is_white_player'] = is_white_player
    data['is_current_turn'] = is_current_turn
    data['opponent'] = UserSerializer(
        game.black_player if is_white_player else game.white_player
    ).data
    
    return Response(data)


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def game_history_view(request):
    """Get game history for the current user"""
    user = request.user
    history = get_user_game_history(user)
    
    # Transform history data for serialization
    history_data = [
        {
            'opponent': item['opponent'],
            'move_count': item['move_count'],
            'outcome': item['outcome'],
            'game_id': item['game'].id,
            'created_at': item['game'].created_at,
        }
        for item in history
    ]
    
    serializer = GameHistorySerializer(history_data, many=True)
    return Response(serializer.data)


@api_view(['GET'])
@permission_classes([AllowAny])
def rules_view(request):
    """Get chess rules content"""
    rules = {
        'title': 'Chess Rules',
        'sections': [
            {
                'title': 'Objective',
                'content': 'The objective of chess is to checkmate your opponent\'s king. Checkmate occurs when the king is in a position to be captured (in check) and cannot escape from capture.'
            },
            {
                'title': 'The Board',
                'content': 'Chess is played on an 8x8 board with 64 squares of alternating colors. Each player starts with 16 pieces: 1 king, 1 queen, 2 rooks, 2 bishops, 2 knights, and 8 pawns.'
            },
            {
                'title': 'Piece Movement',
                'content': '''
                - King: Moves one square in any direction
                - Queen: Moves any number of squares in any direction
                - Rook: Moves any number of squares horizontally or vertically
                - Bishop: Moves any number of squares diagonally
                - Knight: Moves in an "L" shape (2 squares in one direction, then 1 square perpendicular)
                - Pawn: Moves forward one square (or two squares from starting position), captures diagonally
                '''
            },
            {
                'title': 'Special Moves',
                'content': '''
                - Castling: A special move involving the king and a rook
                - En Passant: A special pawn capture
                - Pawn Promotion: When a pawn reaches the opposite end of the board
                '''
            },
            {
                'title': 'Game End',
                'content': '''
                - Checkmate: The king is in check and cannot escape
                - Stalemate: No legal moves available but not in check (draw)
                - Resignation: A player voluntarily concedes the game
                '''
            }
        ]
    }
    return Response(rules)


@api_view(['GET'])
@permission_classes([AllowAny])
def about_view(request):
    """Get about page content"""
    about = {
        'title': 'About This Project',
        'description': 'CSCI 620: Real-Time Multiplayer Chess Game',
        'features': [
            'Real-time multiplayer gameplay using WebSockets',
            'User authentication and registration',
            'Game history tracking',
            'Move validation using python-chess library'
        ],
        'technologies': {
            'backend': ['Django', 'Django REST Framework', 'Django Channels', 'python-chess'],
            'frontend': ['React', 'React Router', 'WebSocket API'],
            'deployment': ['Docker', 'Google Cloud Platform']
        }
    }
    return Response(about)

