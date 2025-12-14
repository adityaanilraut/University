import React, { useState, useEffect } from 'react';
import { contentApi } from '../services/api';
import './ContentPages.css';

const RulesPage = () => {
  const [rules, setRules] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchRules = async () => {
      try {
        const data = await contentApi.getRules();
        setRules(data);
      } catch (err) {
        // Use default rules if API fails
        setRules(getDefaultRules());
      } finally {
        setLoading(false);
      }
    };

    fetchRules();
  }, []);

  if (loading) {
    return (
      <div className="loading-container">
        <div className="loading-spinner"></div>
        <p>Loading rules...</p>
      </div>
    );
  }

  return (
    <div className="page-container content-page">
      <h1 className="page-title">♔ Chess Rules</h1>
      
      <div className="content-grid">
        {rules?.sections?.map((section, index) => (
          <div key={index} className="card content-card" style={{ animationDelay: `${index * 0.1}s` }}>
            <div className="card-header">
              <span className="section-icon">{getSectionIcon(section.title)}</span>
              {section.title}
            </div>
            <div className="card-content">
              {section.content.split('\n').map((line, i) => (
                line.trim().startsWith('-') ? (
                  <div key={i} className="rule-item">
                    <span className="rule-bullet">•</span>
                    <span>{line.trim().substring(1).trim()}</span>
                  </div>
                ) : (
                  <p key={i}>{line}</p>
                )
              ))}
            </div>
          </div>
        ))}
      </div>

      {/* Piece Movement Reference */}
      <div className="card piece-reference">
        <div className="card-header">
          <span className="section-icon">♟</span>
          Piece Reference
        </div>
        <div className="piece-grid">
          {getPieceInfo().map((piece, index) => (
            <div key={index} className="piece-card">
              <span className="piece-symbol">{piece.symbol}</span>
              <span className="piece-name">{piece.name}</span>
              <span className="piece-move">{piece.move}</span>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
};

// Helper functions
const getSectionIcon = (title) => {
  const icons = {
    'Objective': '🎯',
    'The Board': '♜',
    'Piece Movement': '♞',
    'Special Moves': '✨',
    'Game End': '🏆',
  };
  return icons[title] || '📋';
};

const getPieceInfo = () => [
  { symbol: '♔', name: 'King', move: 'One square any direction' },
  { symbol: '♕', name: 'Queen', move: 'Any direction, any distance' },
  { symbol: '♖', name: 'Rook', move: 'Horizontal or vertical' },
  { symbol: '♗', name: 'Bishop', move: 'Diagonal only' },
  { symbol: '♘', name: 'Knight', move: 'L-shape (2+1 squares)' },
  { symbol: '♙', name: 'Pawn', move: 'Forward, captures diagonal' },
];

const getDefaultRules = () => ({
  title: 'Chess Rules',
  sections: [
    {
      title: 'Objective',
      content: 'The objective of chess is to checkmate your opponent\'s king. Checkmate occurs when the king is in a position to be captured (in check) and cannot escape from capture.'
    },
    {
      title: 'The Board',
      content: 'Chess is played on an 8x8 board with 64 squares of alternating colors. Each player starts with 16 pieces: 1 king, 1 queen, 2 rooks, 2 bishops, 2 knights, and 8 pawns.'
    },
    {
      title: 'Piece Movement',
      content: `- King: Moves one square in any direction
- Queen: Moves any number of squares in any direction
- Rook: Moves any number of squares horizontally or vertically
- Bishop: Moves any number of squares diagonally
- Knight: Moves in an "L" shape (2 squares in one direction, then 1 square perpendicular)
- Pawn: Moves forward one square (or two squares from starting position), captures diagonally`
    },
    {
      title: 'Special Moves',
      content: `- Castling: A special move involving the king and a rook
- En Passant: A special pawn capture
- Pawn Promotion: When a pawn reaches the opposite end of the board`
    },
    {
      title: 'Game End',
      content: `- Checkmate: The king is in check and cannot escape
- Stalemate: No legal moves available but not in check (draw)
- Resignation: A player voluntarily concedes the game`
    }
  ]
});

export default RulesPage;

