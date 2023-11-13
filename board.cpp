#include "board.h"

bool Move::IsCapture() { return (bool)(flags & 1); }
bool Move::IsPromotion() { return (bool)((flags >> 1) & 1); }
bool Move::Special0() { return (bool)((flags >> 2) & 1); }
bool Move::Special1() { return (bool)((flags >> 3) & 1); }

unsigned int Move::CreateFlags(const bool& capture, const bool& promotion,
                               const bool& special0, const bool& special1) {
  return ((capture & 1) | ((promotion & 1) << 1) | (special0 & 1) << 2) |
         ((special1 & 1) << 3);
}

Board MovePiece(const int& px, const int& py, const int& nx,
                const int& ny, Board board) {
  board[(ny << 3) + nx] = board[(py << 3) + px];
  board[(py << 3) + px] = Piece(Color::none, PieceType::empty);
  return board;
}

void DrawBoard(const Board& board) {
  std::cout << "\n   +---+---+---+---+---+---+---+---+\n";
  for (int i = 0; i < board.size(); i++) {
    char letter;
    switch (board[i].type) {
      case PieceType::pawn:
        letter = 'p';
        break;
      case PieceType::knight:
        letter = 'n';
        break;
      case PieceType::bishop:
        letter = 'b';
        break;
      case PieceType::rook:
        letter = 'r';
        break;
      case PieceType::king:
        letter = 'k';
        break;
      case PieceType::queen:
        letter = 'q';
        break;

      default:
        letter = ' ';
        break;
    }
    if ((i & 7u) == 0u) {
      std::cout << ' ' << 8 - (i >> 3u) << ' ';
    }
    if (board[i].color == Color::white) {
      std::cout << "| " << (char)toupper(letter) << " ";
    } else {
      std::cout << "| " << letter << " ";
    }
    if ((i & 7u) == 7u) {
      std::cout << "|\n   +---+---+---+---+---+---+---+---+\n";
    }
  }
  std::cout << "     a   b   c   d   e   f   g   h\n";
}