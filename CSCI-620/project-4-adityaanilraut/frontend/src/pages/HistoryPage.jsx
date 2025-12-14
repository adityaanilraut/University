import React, { useState, useEffect } from 'react';
import { gameApi } from '../services/api';
import './HistoryPage.css';

const HistoryPage = () => {
  const [history, setHistory] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchHistory = async () => {
      try {
        const data = await gameApi.getHistory();
        setHistory(data);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    };

    fetchHistory();
  }, []);

  if (loading) {
    return (
      <div className="loading-container">
        <div className="loading-spinner"></div>
        <p>Loading history...</p>
      </div>
    );
  }

  // Calculate stats
  const stats = {
    total: history.length,
    wins: history.filter(g => g.outcome === 'Win').length,
    losses: history.filter(g => g.outcome === 'Loss').length,
    draws: history.filter(g => g.outcome === 'Draw').length,
  };

  return (
    <div className="page-container">
      <h1 className="page-title">Game History</h1>

      {error && (
        <div className="alert alert-error">{error}</div>
      )}

      {/* Stats Summary */}
      <div className="stats-grid">
        <div className="stat-card">
          <span className="stat-value">{stats.total}</span>
          <span className="stat-label">Total Games</span>
        </div>
        <div className="stat-card wins">
          <span className="stat-value">{stats.wins}</span>
          <span className="stat-label">Wins</span>
        </div>
        <div className="stat-card losses">
          <span className="stat-value">{stats.losses}</span>
          <span className="stat-label">Losses</span>
        </div>
        <div className="stat-card draws">
          <span className="stat-value">{stats.draws}</span>
          <span className="stat-label">Draws</span>
        </div>
      </div>

      {/* Games List */}
      <div className="card">
        <div className="card-header">
          <span className="header-icon">📊</span>
          Past Games
        </div>
        
        {history.length > 0 ? (
          <div className="history-table-container">
            <table className="history-table">
              <thead>
                <tr>
                  <th>Opponent</th>
                  <th>Moves</th>
                  <th>Result</th>
                  <th>Date</th>
                </tr>
              </thead>
              <tbody>
                {history.map((game, index) => (
                  <tr key={game.game_id || index} className="history-row">
                    <td className="opponent-cell">
                      <span className="opponent-icon">♟</span>
                      {game.opponent}
                    </td>
                    <td className="moves-cell">{game.move_count}</td>
                    <td>
                      <span className={`badge badge-${
                        game.outcome === 'Win' ? 'success' : 
                        game.outcome === 'Loss' ? 'danger' : 'info'
                      }`}>
                        {game.outcome}
                      </span>
                    </td>
                    <td className="date-cell">
                      {new Date(game.created_at).toLocaleDateString()}
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        ) : (
          <div className="empty-state">
            <div className="empty-icon">♟</div>
            <p>No games played yet</p>
            <small>Start a game from the lobby to see your history here</small>
          </div>
        )}
      </div>
    </div>
  );
};

export default HistoryPage;

