from django.urls import path
from . import api_views

urlpatterns = [
    # Auth endpoints
    path('api/auth/csrf/', api_views.get_csrf_token, name='csrf_token'),
    path('api/auth/user/', api_views.get_current_user, name='current_user'),
    path('api/auth/login/', api_views.login_view, name='login'),
    path('api/auth/register/', api_views.register_view, name='register'),
    path('api/auth/logout/', api_views.logout_view, name='logout'),
    
    # Game endpoints
    path('api/lobby/', api_views.lobby_view, name='lobby'),
    path('api/games/<int:game_id>/', api_views.game_detail_view, name='game_detail'),
    path('api/games/history/', api_views.game_history_view, name='game_history'),
    
    # Static content endpoints
    path('api/rules/', api_views.rules_view, name='rules'),
    path('api/about/', api_views.about_view, name='about'),
]
