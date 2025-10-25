// Chess piece Unicode characters
const pieces = {
    white: {
        king: '&#9812;',
        queen: '&#9813;',
        rook: '&#9814;',
        bishop: '&#9815;',
        knight: '&#9816;',
        pawn: '&#9817;'
    },
    black: {
        king: '&#9818;',
        queen: '&#9819;',
        rook: '&#9820;',
        bishop: '&#9821;',
        knight: '&#9822;',
        pawn: '&#9823;'
    }
};

// Starting position of chess pieces
const startingPosition = {
    'a8': pieces.black.rook, 'b8': pieces.black.knight, 'c8': pieces.black.bishop, 'd8': pieces.black.queen,
    'e8': pieces.black.king, 'f8': pieces.black.bishop, 'g8': pieces.black.knight, 'h8': pieces.black.rook,
    'a7': pieces.black.pawn, 'b7': pieces.black.pawn, 'c7': pieces.black.pawn, 'd7': pieces.black.pawn,
    'e7': pieces.black.pawn, 'f7': pieces.black.pawn, 'g7': pieces.black.pawn, 'h7': pieces.black.pawn,
    'a6': '&nbsp;', 'b6': '&nbsp;', 'c6': '&nbsp;', 'd6': '&nbsp;',
    'e6': '&nbsp;', 'f6': '&nbsp;', 'g6': '&nbsp;', 'h6': '&nbsp;',
    'a5': '&nbsp;', 'b5': '&nbsp;', 'c5': '&nbsp;', 'd5': '&nbsp;',
    'e5': '&nbsp;', 'f5': '&nbsp;', 'g5': '&nbsp;', 'h5': '&nbsp;',
    'a4': '&nbsp;', 'b4': '&nbsp;', 'c4': '&nbsp;', 'd4': '&nbsp;',
    'e4': '&nbsp;', 'f4': '&nbsp;', 'g4': '&nbsp;', 'h4': '&nbsp;',
    'a3': '&nbsp;', 'b3': '&nbsp;', 'c3': '&nbsp;', 'd3': '&nbsp;',
    'e3': '&nbsp;', 'f3': '&nbsp;', 'g3': '&nbsp;', 'h3': '&nbsp;',
    'a2': pieces.white.pawn, 'b2': pieces.white.pawn, 'c2': pieces.white.pawn, 'd2': pieces.white.pawn,
    'e2': pieces.white.pawn, 'f2': pieces.white.pawn, 'g2': pieces.white.pawn, 'h2': pieces.white.pawn,
    'a1': pieces.white.rook, 'b1': pieces.white.knight, 'c1': pieces.white.bishop, 'd1': pieces.white.queen,
    'e1': pieces.white.king, 'f1': pieces.white.bishop, 'g1': pieces.white.knight, 'h1': pieces.white.rook
};

// Current board state
let currentBoard = { ...startingPosition };

// Initialize the chessboard when the page loads
function initializeChessboard() {
    const container = document.getElementById('chessboard-container');
    container.innerHTML = '';
    
    const table = document.createElement('table');
    
    // Create column headers (8, 7, 6, 5, 4, 3, 2, 1)
    const headerRow = document.createElement('tr');
    headerRow.appendChild(document.createElement('th')); // Empty cell for corner
    
    for (let col = 0; col < 8; col++) {
        const th = document.createElement('th');
        th.textContent = 8 - col;
        headerRow.appendChild(th);
    }
    
    headerRow.appendChild(document.createElement('th')); // Empty cell for corner
    table.appendChild(headerRow);
    
    // Create board rows
    for (let row = 0; row < 8; row++) {
        const tr = document.createElement('tr');
        
        // Add row label (a, b, c, d, e, f, g, h)
        const rowLabel = document.createElement('th');
        rowLabel.textContent = String.fromCharCode(97 + row);
        tr.appendChild(rowLabel);
        
        // Add board cells
        for (let col = 0; col < 8; col++) {
            const td = document.createElement('td');
            const square = String.fromCharCode(97 + col) + (8 - row);
            td.id = square;
            td.innerHTML = currentBoard[square] || '&nbsp;';
            tr.appendChild(td);
        }
        
        // Add row label again on the right
        const rowLabelRight = document.createElement('th');
        rowLabelRight.textContent = String.fromCharCode(97 + row);
        tr.appendChild(rowLabelRight);
        
        table.appendChild(tr);
    }
    
    // Create bottom row with column headers
    const bottomRow = document.createElement('tr');
    bottomRow.appendChild(document.createElement('th')); // Empty cell for corner
    
    for (let col = 0; col < 8; col++) {
        const th = document.createElement('th');
        th.textContent = 8 - col;
        bottomRow.appendChild(th);
    }
    
    bottomRow.appendChild(document.createElement('th')); // Empty cell for corner
    table.appendChild(bottomRow);
    
    container.appendChild(table);
}

// Move a chess piece
function movePiece() {
    const srcSquare = document.getElementById('src').value.toLowerCase();
    const dstSquare = document.getElementById('dst').value.toLowerCase();
    
    // Validate input format
    if (!isValidSquare(srcSquare) || !isValidSquare(dstSquare)) {
        alert('Please enter valid square coordinates (e.g., e2, e4)');
        return;
    }
    
    // Check if source square has a piece
    if (!currentBoard[srcSquare] || currentBoard[srcSquare] === '&nbsp;') {
        alert('No piece found at source square');
        return;
    }
    
    // Perform the move
    const piece = currentBoard[srcSquare];
    currentBoard[dstSquare] = piece;
    currentBoard[srcSquare] = '&nbsp;';
    
    // Update the display
    document.getElementById(srcSquare).innerHTML = '&nbsp;';
    document.getElementById(dstSquare).innerHTML = piece;
    
    // Clear the input fields
    document.getElementById('src').value = '';
    document.getElementById('dst').value = '';
}

// Reset the board to starting position
function resetBoard() {
    currentBoard = { ...startingPosition };
    initializeChessboard();
    
    // Clear the input fields
    document.getElementById('src').value = '';
    document.getElementById('dst').value = '';
}

// Validate square notation (a1-h8)
function isValidSquare(square) {
    if (square.length !== 2) return false;
    const file = square[0];
    const rank = square[1];
    return file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8';
}

// Initialize the chessboard when the page loads
document.addEventListener('DOMContentLoaded', function() {
    initializeChessboard();
});
