import React, { useState, useEffect, useCallback, useRef } from 'react';
import { useNavigate } from 'react-router-dom';
import { useAuth } from '../contexts/AuthContext';
import { gameApi } from '../services/api';
import { LobbyWebSocket } from '../services/websocket';
import './LobbyPage.css';

const LobbyPage = () => {
  const { user } = useAuth();
  const navigate = useNavigate();
  
  const [lobbyData, setLobbyData] = useState({
    available_players: [],
    pending_challenges: [],
    my_challenges: [],
    active_game_id: null,
  });
  const [loading, setLoading] = useState(true);
  const [notification, setNotification] = useState(null);
  
  const wsRef = useRef(null);

  // Check for active game and redirect
  useEffect(() => {
    if (lobbyData.active_game_id) {
      navigate(`/game/${lobbyData.active_game_id}`);
    }
  }, [lobbyData.active_game_id, navigate]);

  // Handle lobby data updates
  const handleLobbyUpdate = useCallback((data) => {
    setLobbyData(prev => ({
      ...prev,
      available_players: data.available_players || [],
      pending_challenges: data.pending_challenges || [],
      my_challenges: data.my_challenges || [],
    }));
    setLoading(false);
  }, []);

  // Handle new game notification
  const handleNewGame = useCallback((gameId) => {
    setNotification({ type: 'success', message: 'Challenge accepted! Starting game...' });
    setTimeout(() => {
      navigate(`/game/${gameId}`);
    }, 1000);
  }, [navigate]);

  // Handle challenge sent notification
  const handleChallengeSent = useCallback((message) => {
    setNotification({ type: 'success', message });
  }, []);

  // Handle errors
  const handleError = useCallback((error) => {
    setNotification({ type: 'error', message: error.message || 'An error occurred' });
  }, []);

  // Fetch initial lobby data and setup WebSocket
  useEffect(() => {
    const fetchLobby = async () => {
      try {
        const data = await gameApi.getLobby();
        setLobbyData(data);
        
        // Check for active game
        if (data.active_game_id) {
          navigate(`/game/${data.active_game_id}`);
          return;
        }
      } catch (err) {
        handleError(err);
      } finally {
        setLoading(false);
      }
    };

    fetchLobby();

    // Setup WebSocket
    wsRef.current = new LobbyWebSocket();
    wsRef.current.connect({
      onLobbyUpdate: handleLobbyUpdate,
      onNewGame: handleNewGame,
      onChallengeSent: handleChallengeSent,
      onError: handleError,
    });

    return () => {
      if (wsRef.current) {
        wsRef.current.disconnect();
        wsRef.current = null;
      }
    };
  }, [navigate, handleLobbyUpdate, handleNewGame, handleChallengeSent, handleError]);

  // Send challenge to a player
  const sendChallenge = (playerId) => {
    if (wsRef.current) {
      wsRef.current.sendChallenge(playerId);
    }
  };

  // Respond to a challenge
  const respondChallenge = (challengeId, response) => {
    if (wsRef.current) {
      wsRef.current.respondChallenge(challengeId, response);
    }
  };

  // Clear notification
  useEffect(() => {
    if (notification) {
      const timer = setTimeout(() => setNotification(null), 5000);
      return () => clearTimeout(timer);
    }
  }, [notification]);

  if (loading) {
    return (
      <div className="loading-container">
        <div className="loading-spinner"></div>
        <p>Loading lobby...</p>
      </div>
    );
  }

  return (
    <div className="page-container">
      <h1 className="page-title">Welcome, {user?.username}!</h1>

      {notification && (
        <div className={`alert alert-${notification.type}`}>
          {notification.message}
        </div>
      )}

      <div className="lobby-grid">
        {/* Available Players */}
        <div className="card">
          <div className="card-header">
            <span className="header-icon">♟</span>
            Available Players
          </div>
          <div className="player-list">
            {lobbyData.available_players.length > 0 ? (
              lobbyData.available_players.map(player => (
                <div key={player.id} className="list-item player-item">
                  <span className="player-name">{player.username}</span>
                  <button 
                    className="btn btn-primary btn-sm"
                    onClick={() => sendChallenge(player.id)}
                  >
                    Challenge
                  </button>
                </div>
              ))
            ) : (
              <div className="empty-state">
                <p>No players available</p>
                <small>Wait for other players to join</small>
              </div>
            )}
          </div>
        </div>

        {/* Pending Challenges */}
        <div className="card">
          <div className="card-header">
            <span className="header-icon">⚔️</span>
            Incoming Challenges
          </div>
          <div className="challenge-list">
            {lobbyData.pending_challenges.length > 0 ? (
              lobbyData.pending_challenges.map(challenge => (
                <div key={challenge.id} className="list-item challenge-item">
                  <div className="challenge-info">
                    <span className="challenger-name">
                      {challenge.challenger.username}
                    </span>
                    <span className="challenge-time">
                      {new Date(challenge.created_at).toLocaleTimeString()}
                    </span>
                  </div>
                  <div className="challenge-actions">
                    <button 
                      className="btn btn-success btn-sm"
                      onClick={() => respondChallenge(challenge.id, 'accept')}
                    >
                      Accept
                    </button>
                    <button 
                      className="btn btn-danger btn-sm"
                      onClick={() => respondChallenge(challenge.id, 'decline')}
                    >
                      Decline
                    </button>
                  </div>
                </div>
              ))
            ) : (
              <div className="empty-state">
                <p>No pending challenges</p>
                <small>Challenge a player to start a game</small>
              </div>
            )}
          </div>
        </div>

        {/* My Challenges */}
        {lobbyData.my_challenges.length > 0 && (
          <div className="card my-challenges-card">
            <div className="card-header">
              <span className="header-icon">📤</span>
              Sent Challenges
            </div>
            <div className="challenge-list">
              {lobbyData.my_challenges.map(challenge => (
                <div key={challenge.id} className="list-item">
                  <span>Challenged {challenge.opponent.username}</span>
                  <span className="badge badge-warning">Pending</span>
                </div>
              ))}
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default LobbyPage;

