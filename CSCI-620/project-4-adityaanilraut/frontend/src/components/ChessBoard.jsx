import React, { useMemo } from 'react';
import './ChessBoard.css';

// Unicode chess pieces
const PIECE_SYMBOLS = {
  'K': '♔', 'Q': '♕', 'R': '♖', 'B': '♗', 'N': '♘', 'P': '♙',
  'k': '♚', 'q': '♛', 'r': '♜', 'b': '♝', 'n': '♞', 'p': '♟',
};

// Parse FEN string to get board state
const parseFEN = (fen) => {
  const [position] = fen.split(' ');
  const rows = position.split('/');
  const board = [];
  
  for (const row of rows) {
    const boardRow = [];
    for (const char of row) {
      if (isNaN(char)) {
        boardRow.push(char);
      } else {
        for (let i = 0; i < parseInt(char); i++) {
          boardRow.push(null);
        }
      }
    }
    board.push(boardRow);
  }
  
  return board;
};

const ChessBoard = ({ 
  boardState, 
  isWhitePlayer 
}) => {
  const board = useMemo(() => parseFEN(boardState), [boardState]);
  const isFlipped = !isWhitePlayer;

  // Get displayed board (flip if black player)
  const displayBoard = useMemo(() => {
    if (isFlipped) {
      return board.map(row => [...row].reverse()).reverse();
    }
    return board;
  }, [board, isFlipped]);

  // Get file and rank labels
  const files = isFlipped ? 'hgfedcba'.split('') : 'abcdefgh'.split('');
  const ranks = isFlipped ? '12345678'.split('') : '87654321'.split('');

  return (
    <div className="chess-board-container">
      <div className="chess-board">
        {/* Column labels (top) */}
        <div className="board-row labels-row">
          <div className="label-cell corner"></div>
          {files.map(file => (
            <div key={file} className="label-cell file-label">{file}</div>
          ))}
          <div className="label-cell corner"></div>
        </div>

        {/* Board rows */}
        {displayBoard.map((row, rowIndex) => (
          <div key={rowIndex} className="board-row">
            {/* Rank label (left) */}
            <div className="label-cell rank-label">{ranks[rowIndex]}</div>
            
            {/* Squares */}
            {row.map((piece, colIndex) => {
              const isLight = (rowIndex + colIndex) % 2 === 0;
              
              return (
                <div
                  key={colIndex}
                  className={`square ${isLight ? 'light' : 'dark'}`}
                >
                  {piece && (
                    <span className={`piece ${piece === piece.toUpperCase() ? 'white-piece' : 'black-piece'}`}>
                      {PIECE_SYMBOLS[piece]}
                    </span>
                  )}
                </div>
              );
            })}
            
            {/* Rank label (right) */}
            <div className="label-cell rank-label">{ranks[rowIndex]}</div>
          </div>
        ))}

        {/* Column labels (bottom) */}
        <div className="board-row labels-row">
          <div className="label-cell corner"></div>
          {files.map(file => (
            <div key={file} className="label-cell file-label">{file}</div>
          ))}
          <div className="label-cell corner"></div>
        </div>
      </div>
    </div>
  );
};

export default ChessBoard;

