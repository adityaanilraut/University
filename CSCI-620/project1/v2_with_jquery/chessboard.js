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
    const $container = $('#chessboard-container');
    $container.empty();
    
    const $table = $('<table>');
    
    // Create column headers (8, 7, 6, 5, 4, 3, 2, 1)
    const $headerRow = $('<tr>');
    $headerRow.append($('<th>'));
    
    for (let col = 0; col < 8; col++) {
        const $th = $('<th>').text(8 - col);
        $headerRow.append($th);
    }
    
    $headerRow.append($('<th>'));
    $table.append($headerRow);
    
    // Create board rows
    for (let row = 0; row < 8; row++) {
        const $tr = $('<tr>');
        
        // Add row label (a, b, c, d, e, f, g, h)
        const $rowLabel = $('<th>').text(String.fromCharCode(97 + row));
        $tr.append($rowLabel);
        
        // Add board cells
        for (let col = 0; col < 8; col++) {
            const $td = $('<td>');
            const square = String.fromCharCode(97 + col) + (8 - row);
            $td.attr('id', square);
            $td.html(currentBoard[square] || '&nbsp;');
            $tr.append($td);
        }
        
        // Add row label again on the right
        const $rowLabelRight = $('<th>').text(String.fromCharCode(97 + row));
        $tr.append($rowLabelRight);
        
        $table.append($tr);
    }
    
    // Create bottom row with column headers
    const $bottomRow = $('<tr>');
    $bottomRow.append($('<th>'));
    
    for (let col = 0; col < 8; col++) {
        const $th = $('<th>').text(8 - col);
        $bottomRow.append($th);
    }
    
    $bottomRow.append($('<th>'));
    $table.append($bottomRow);
    
    $container.append($table);
}

// Move a chess piece
function movePiece() {
    const srcSquare = $('#src').val().toLowerCase();
    const dstSquare = $('#dst').val().toLowerCase();
    
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
    
    // Update the display using jQuery
    $('#' + srcSquare).html('&nbsp;');
    $('#' + dstSquare).html(piece);
    
    // Clear the input fields
    $('#src').val('');
    $('#dst').val('');
}

// Reset the board to starting position
function resetBoard() {
    currentBoard = { ...startingPosition };
    initializeChessboard();
    
    // Clear the input fields
    $('#src').val('');
    $('#dst').val('');
}

// Validate square notation (a1-h8)
function isValidSquare(square) {
    if (square.length !== 2) return false;
    const file = square[0];
    const rank = square[1];
    return file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8';
}

// Initialize when document is ready
$(document).ready(function() {
    initializeChessboard();
    
    // Bind event handlers using jQuery
    $('#move-btn').click(function() {
        movePiece();
    });
    
    $('#reset-btn').click(function() {
        resetBoard();
    });
    
    // Allow Enter key to trigger move
    $('#src, #dst').keypress(function(e) {
        if (e.which === 13) { // Enter key
            movePiece();
        }
    });
});
