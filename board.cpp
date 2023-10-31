#include "board.h"

Piece GetPiece(const size_t& x, const size_t& y, const Board& board) {
  return board[8 * y + x];
}

Board MovePiece(const size_t& px, const size_t& py, const size_t& nx,
                const size_t& ny, Board board) {
  board[8 * ny + nx] = GetPiece(px, py, board);
  board[8 * py + px] = Piece(' ', ' ');
  return board;
}

void DrawBoard(const Board& board) {
  std::cout << "\n   +---+---+---+---+---+---+---+---+\n";
  for (size_t i = 0; i < board.size(); i++) {
    if ((i & 7u) == 0u) {
      std::cout << ' ' << 8 - (i >> 3u) << ' ';
    }
    if (board[i].color == 'w') {
      std::cout << "| " << (char)toupper(board[i].type) << " ";
    } else {
      std::cout << "| " << board[i].type << " ";
    }
    if ((i & 7u) == 7u) {
      std::cout << "|\n   +---+---+---+---+---+---+---+---+\n";
    }
  }
  std::cout << "     a   b   c   d   e   f   g   h\n";
}