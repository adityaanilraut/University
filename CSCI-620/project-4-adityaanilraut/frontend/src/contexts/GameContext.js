import React, { createContext, useContext, useState, useEffect, useCallback, useRef } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import { gameApi } from '../services/api';
import { GameWebSocket } from '../services/websocket';

const GameContext = createContext(null);

export const useGame = () => {
  const context = useContext(GameContext);
  if (!context) {
    throw new Error('useGame must be used within a GameProvider');
  }
  return context;
};

export const GameProvider = ({ children }) => {
  const { gameId } = useParams();
  const navigate = useNavigate();
  
  const [game, setGame] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [notification, setNotification] = useState(null);
  
  const wsRef = useRef(null);

  // Fetch initial game data
  const fetchGame = useCallback(async () => {
    if (!gameId) return;
    
    try {
      setLoading(true);
      const data = await gameApi.getGame(gameId);
      setGame(data);
      setError(null);
    } catch (err) {
      setError(err.message);
      if (err.message.includes('not authorized') || err.message.includes('not found')) {
        navigate('/lobby');
      }
    } finally {
      setLoading(false);
    }
  }, [gameId, navigate]);

  // Handle WebSocket game state updates
  const handleGameStateUpdate = useCallback((gameState) => {
    setGame(prevGame => {
      if (!prevGame) return prevGame;
      
      // Check if game just ended
      if (gameState.status === 'completed' && prevGame.status !== 'completed') {
        let message = 'Game Over! ';
        if (gameState.outcome === 'checkmate') {
          message += `Checkmate! ${gameState.winner} wins!`;
        } else if (gameState.outcome === 'stalemate') {
          message += 'Stalemate - Draw!';
        } else if (gameState.outcome === 'resignation') {
          message += `${gameState.winner} wins by resignation!`;
        }
        setNotification({ type: 'info', message });
      }
      
      // Update game state
      return {
        ...prevGame,
        board_state: gameState.board_state,
        current_turn: gameState.current_turn,
        is_current_turn: gameState.is_current_turn,
        status: gameState.status,
        outcome: gameState.outcome,
        winner: gameState.winner ? { username: gameState.winner } : null,
      };
    });
  }, []);

  // Handle WebSocket errors
  const handleWsError = useCallback((err) => {
    setNotification({ type: 'error', message: err.message || 'Connection error' });
  }, []);

  // Initialize WebSocket connection
  useEffect(() => {
    if (!gameId) return;

    // Fetch initial game data
    fetchGame();

    // Connect WebSocket
    wsRef.current = new GameWebSocket(gameId);
    wsRef.current.connect(handleGameStateUpdate, handleWsError);

    // Cleanup on unmount
    return () => {
      if (wsRef.current) {
        wsRef.current.disconnect();
        wsRef.current = null;
      }
    };
  }, [gameId, fetchGame, handleGameStateUpdate, handleWsError]);

  // Send move
  const makeMove = useCallback((fromSquare, toSquare) => {
    if (!wsRef.current) {
      setNotification({ type: 'error', message: 'Not connected to game' });
      return false;
    }
    
    const success = wsRef.current.sendMove(fromSquare.toLowerCase(), toSquare.toLowerCase());
    if (!success) {
      setNotification({ type: 'error', message: 'Failed to send move' });
    }
    return success;
  }, []);

  // Resign game
  const resign = useCallback(() => {
    if (!wsRef.current) {
      setNotification({ type: 'error', message: 'Not connected to game' });
      return false;
    }
    
    const success = wsRef.current.sendResign();
    if (!success) {
      setNotification({ type: 'error', message: 'Failed to resign' });
    }
    return success;
  }, []);

  // Clear notification
  const clearNotification = useCallback(() => {
    setNotification(null);
  }, []);

  // Navigate back to lobby
  const goToLobby = useCallback(() => {
    navigate('/lobby');
  }, [navigate]);

  const value = {
    game,
    loading,
    error,
    notification,
    makeMove,
    resign,
    clearNotification,
    goToLobby,
    refreshGame: fetchGame,
  };

  return (
    <GameContext.Provider value={value}>
      {children}
    </GameContext.Provider>
  );
};

export default GameContext;

