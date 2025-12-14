import React, { useState, useEffect } from 'react';
import { useGame } from '../contexts/GameContext';
import ChessBoard from '../components/ChessBoard';
import './GamePage.css';

const GamePage = () => {
  const { 
    game, 
    loading, 
    error, 
    notification, 
    makeMove, 
    resign, 
    clearNotification,
    goToLobby 
  } = useGame();

  const [moveFrom, setMoveFrom] = useState('');
  const [moveTo, setMoveTo] = useState('');

  // Clear notification after delay
  useEffect(() => {
    if (notification) {
      const timer = setTimeout(clearNotification, 5000);
      return () => clearTimeout(timer);
    }
  }, [notification, clearNotification]);

  // Handle manual move input
  const handleManualMove = (e) => {
    e.preventDefault();
    if (moveFrom && moveTo) {
      makeMove(moveFrom, moveTo);
      setMoveFrom('');
      setMoveTo('');
    }
  };

  // Handle resign
  const handleResign = () => {
    if (window.confirm('Are you sure you want to resign? You will lose the game.')) {
      resign();
    }
  };

  if (loading) {
    return (
      <div className="loading-container">
        <div className="loading-spinner"></div>
        <p>Loading game...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="page-container">
        <div className="alert alert-error">{error}</div>
        <button onClick={goToLobby} className="btn btn-primary">
          Return to Lobby
        </button>
      </div>
    );
  }

  if (!game) {
    return (
      <div className="page-container">
        <div className="alert alert-error">Game not found</div>
        <button onClick={goToLobby} className="btn btn-primary">
          Return to Lobby
        </button>
      </div>
    );
  }

  const isGameOver = game.status === 'completed';

  return (
    <div className="page-container game-page">
      {notification && (
        <div className={`alert alert-${notification.type}`}>
          {notification.message}
        </div>
      )}

      {/* Game Header */}
      <div className="game-header">
        <h1 className="game-title">
          Game #{game.id}
        </h1>
        <div className="game-players">
          <span className={`player ${game.current_turn === 'white' ? 'active' : ''}`}>
            <span className="player-piece">♔</span>
            {game.white_player.username}
          </span>
          <span className="vs">VS</span>
          <span className={`player ${game.current_turn === 'black' ? 'active' : ''}`}>
            <span className="player-piece">♚</span>
            {game.black_player.username}
          </span>
        </div>
      </div>

      <div className="game-content">
        {/* Chess Board */}
        <div className="board-section">
          <div className="turn-indicator">
            {isGameOver ? (
              <span className="badge badge-info">Game Over</span>
            ) : game.is_current_turn ? (
              <span className="badge badge-success">Your Turn</span>
            ) : (
              <span className="badge badge-warning">Opponent's Turn</span>
            )}
          </div>

          <ChessBoard
            boardState={game.board_state}
            isWhitePlayer={game.is_white_player}
          />

          {/* Move Controls */}
          {!isGameOver && game.is_current_turn && (
            <div className="move-controls">
              <form onSubmit={handleManualMove} className="move-form">
                <div className="move-inputs">
                  <input
                    type="text"
                    className="form-input move-input"
                    placeholder="From (e.g., e2)"
                    value={moveFrom}
                    onChange={(e) => setMoveFrom(e.target.value.toLowerCase())}
                    maxLength={2}
                  />
                  <span className="move-arrow">→</span>
                  <input
                    type="text"
                    className="form-input move-input"
                    placeholder="To (e.g., e4)"
                    value={moveTo}
                    onChange={(e) => setMoveTo(e.target.value.toLowerCase())}
                    maxLength={2}
                  />
                  <button type="submit" className="btn btn-primary">
                    Move
                  </button>
                </div>
              </form>
              <button onClick={handleResign} className="btn btn-danger">
                Resign
              </button>
            </div>
          )}

          {/* Game Over Message */}
          {isGameOver && (
            <div className="game-over-section">
              <div className="game-over-message">
                {game.outcome === 'checkmate' && (
                  <>
                    <h2>Checkmate!</h2>
                    <p>{game.winner?.username} wins!</p>
                  </>
                )}
                {game.outcome === 'stalemate' && (
                  <>
                    <h2>Stalemate!</h2>
                    <p>The game is a draw.</p>
                  </>
                )}
                {game.outcome === 'resignation' && (
                  <>
                    <h2>Game Over</h2>
                    <p>{game.winner?.username} wins by resignation!</p>
                  </>
                )}
              </div>
              <button onClick={goToLobby} className="btn btn-primary">
                Return to Lobby
              </button>
            </div>
          )}
        </div>

        {/* Game Info Sidebar */}
        <div className="game-sidebar">
          {/* Game Information */}
          <div className="card">
            <div className="card-header">
              <span className="header-icon">ℹ️</span>
              Game Information
            </div>
            <div className="info-list">
              <div className="info-item">
                <span className="info-label">White Player</span>
                <span className="info-value">{game.white_player.username}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Black Player</span>
                <span className="info-value">{game.black_player.username}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Your Color</span>
                <span className="info-value">{game.is_white_player ? 'White ♔' : 'Black ♚'}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Status</span>
                <span className={`badge ${isGameOver ? 'badge-info' : 'badge-success'}`}>
                  {game.status}
                </span>
              </div>
            </div>
          </div>

          {/* Move History */}
          <div className="card">
            <div className="card-header">
              <span className="header-icon">📜</span>
              Move History
            </div>
            <div className="move-history">
              {game.moves && game.moves.length > 0 ? (
                <div className="move-list">
                  {game.moves.slice(-10).map((move, index) => (
                    <div key={move.id || index} className="move-item">
                      <span className="move-number">{move.move_number}.</span>
                      <span className="move-notation">{move.move_notation}</span>
                      <span className="move-player">{move.player.username}</span>
                    </div>
                  ))}
                  {game.moves.length > 10 && (
                    <p className="text-muted">Showing last 10 of {game.moves.length} moves</p>
                  )}
                </div>
              ) : (
                <div className="empty-state">No moves yet</div>
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default GamePage;

