from rest_framework import serializers
from django.contrib.auth.models import User
from .models import Game, Challenge, Move


class UserSerializer(serializers.ModelSerializer):
    """Serializer for User model"""
    class Meta:
        model = User
        fields = ['id', 'username']


class UserRegistrationSerializer(serializers.ModelSerializer):
    """Serializer for user registration"""
    password = serializers.CharField(write_only=True, min_length=8)
    password_confirm = serializers.CharField(write_only=True)

    class Meta:
        model = User
        fields = ['username', 'password', 'password_confirm']

    def validate(self, data):
        if data['password'] != data['password_confirm']:
            raise serializers.ValidationError({'password_confirm': 'Passwords do not match'})
        return data

    def create(self, validated_data):
        validated_data.pop('password_confirm')
        user = User.objects.create_user(
            username=validated_data['username'],
            password=validated_data['password']
        )
        return user


class MoveSerializer(serializers.ModelSerializer):
    """Serializer for Move model"""
    player = UserSerializer(read_only=True)

    class Meta:
        model = Move
        fields = ['id', 'player', 'move_notation', 'move_number', 'created_at']


class GameSerializer(serializers.ModelSerializer):
    """Serializer for Game model"""
    white_player = UserSerializer(read_only=True)
    black_player = UserSerializer(read_only=True)
    winner = UserSerializer(read_only=True)
    moves = MoveSerializer(many=True, read_only=True)

    class Meta:
        model = Game
        fields = [
            'id', 'white_player', 'black_player', 'board_state',
            'current_turn', 'status', 'winner', 'outcome',
            'created_at', 'updated_at', 'moves'
        ]


class GameListSerializer(serializers.ModelSerializer):
    """Lightweight serializer for game lists"""
    white_player = UserSerializer(read_only=True)
    black_player = UserSerializer(read_only=True)
    winner = UserSerializer(read_only=True)
    move_count = serializers.SerializerMethodField()

    class Meta:
        model = Game
        fields = [
            'id', 'white_player', 'black_player', 'status',
            'winner', 'outcome', 'created_at', 'move_count'
        ]

    def get_move_count(self, obj):
        return obj.moves.count()


class ChallengeSerializer(serializers.ModelSerializer):
    """Serializer for Challenge model"""
    challenger = UserSerializer(read_only=True)
    opponent = UserSerializer(read_only=True)

    class Meta:
        model = Challenge
        fields = ['id', 'challenger', 'opponent', 'status', 'created_at']


class LobbyDataSerializer(serializers.Serializer):
    """Serializer for lobby data"""
    available_players = UserSerializer(many=True)
    pending_challenges = ChallengeSerializer(many=True)
    my_challenges = ChallengeSerializer(many=True)


class GameHistorySerializer(serializers.Serializer):
    """Serializer for game history data"""
    opponent = serializers.CharField()
    move_count = serializers.IntegerField()
    outcome = serializers.CharField()
    game_id = serializers.IntegerField()
    created_at = serializers.DateTimeField()

