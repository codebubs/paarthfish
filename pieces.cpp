#include "pieces.h"

void Movement(const int& x, const int& y, const Board& board, MoveList& moves) {
  switch (board[(y << 3) + x].type) {
    case PieceType::pawn:
      if (board[(y << 3) + x].color == Color::white) {
        if (y > 0) {
          if (board[((y - 1) << 3) + x].type == PieceType::empty) {
            moves.push_back(MovePiece(x, y, x, y - 1, board));
          }
          if (board[((y - 1) << 3) + x - 1].color == Color::black) {
            moves.push_back(MovePiece(x, y, x - 1, y - 1, board));
          }
          if (board[((y - 1) << 3) + x + 1].color == Color::black) {
            moves.push_back(MovePiece(x, y, x + 1, y - 1, board));
          }
          if (y == 6) {
            if (board[((y - 2) << 3) + x].type == PieceType::empty) {
              moves.push_back(MovePiece(x, y, x, y - 2, board));
            }
          }
        }
      } else {
        if (y < 7) {
          if (board[((y + 1) << 3) + x].type == PieceType::empty) {
            moves.push_back(MovePiece(x, y, x, y + 1, board));
          }
          if (board[((y + 1) << 3) + x - 1].color == Color::white) {
            moves.push_back(MovePiece(x, y, x - 1, y + 1, board));
          }
          if (board[((y + 1) << 3) + x + 1].color == Color::white) {
            moves.push_back(MovePiece(x, y, x + 1, y + 1, board));
          }
          if (y == 1) {
            if (board[((y + 2) << 3) + x].type == PieceType::empty) {
              moves.push_back(MovePiece(x, y, x, y + 2, board));
            }
          }
        }
      }
      break;
    case PieceType::knight:
      if (board[(y << 3) + x].color == Color::white) {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(MovePiece(x, y, x + 2, y - 1, board));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(MovePiece(x, y, x + 2, y + 1, board));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(MovePiece(x, y, x - 2, y - 1, board));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(MovePiece(x, y, x - 2, y + 1, board));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(MovePiece(x, y, x - 1, y - 2, board));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(MovePiece(x, y, x + 1, y - 2, board));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(MovePiece(x, y, x - 1, y + 2, board));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(MovePiece(x, y, x + 1, y + 2, board));
          }
        }
      } else {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(MovePiece(x, y, x + 2, y - 1, board));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(MovePiece(x, y, x + 2, y + 1, board));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(MovePiece(x, y, x - 2, y - 1, board));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(MovePiece(x, y, x - 2, y + 1, board));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(MovePiece(x, y, x - 1, y - 2, board));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(MovePiece(x, y, x + 1, y - 2, board));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(MovePiece(x, y, x - 1, y + 2, board));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(MovePiece(x, y, x + 1, y + 2, board));
          }
        }
      }
      break;
    case PieceType::bishop: {
      int i = 1;
      if (board[(y << 3) + i].color == Color::white) {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y + i, board));
          if (board[((y + i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y + i, board));
          if (board[((y + i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y - i, board));
          if (board[((y - i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y - i, board));
          if (board[((y - i) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y + i, board));
          if (board[((y + i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y + i, board));
          if (board[((y + i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y - i, board));
          if (board[((y - i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y - i, board));
          if (board[((y - i) << 3) + x - i].color == Color::white) break;
          i++;
        }
      }
      break;
    }
    case PieceType::rook: {
      int i = 1;
      if (board[(y << 3) + i].color == Color::white) {
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y + i, board));
          if (board[((y + i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y - i, board));
          if (board[((y - i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y, board));
          if (board[((y) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y, board));
          if (board[((y) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          moves.push_back(MovePiece(x, y, x, y + i, board));
          if (board[((y + i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          moves.push_back(MovePiece(x, y, x, y - i, board));
          if (board[((y - i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y, board));
          if (board[((y) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y, board));
          if (board[((y) << 3) + x - i].color == Color::white) break;
          i++;
        }
      }
      break;
    }
    case PieceType::queen: {
      int i = 1;
      if (board[(y << 3) + i].color == Color::white) {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y + i, board));
          if (board[((y + i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y + i, board));
          if (board[((y + i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y - i, board));
          if (board[((y - i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y - i, board));
          if (board[((y - i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y + i, board));
          if (board[((y + i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y - i, board));
          if (board[((y - i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + i, y, board));
          if (board[((y) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - i, y, board));
          if (board[((y) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y + i, board));
          if (board[((y + i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y + i, board));
          if (board[((y + i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y - i, board));
          if (board[((y - i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i <= 7 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y - i, board));
          if (board[((y - i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          moves.push_back(MovePiece(x, y, x, y + i, board));
          if (board[((y + i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          moves.push_back(MovePiece(x, y, x, y - i, board));
          if (board[((y - i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x + i, y, board));
          if (board[((y) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          moves.push_back(MovePiece(x, y, x - i, y, board));
          if (board[((y) << 3) + x - i].color == Color::white) break;
          i++;
        }
      }
      break;
    }
    case PieceType::king:
      if (board[(y << 3) + x].color == Color::white) {
        if (board[(y << 3) + x + 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + 1, y, board));
        }
        if (board[(y << 3) + x - 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - 1, y, board));
        }
        if (board[((y + 1) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y + 1, board));
        }
        if (board[((y + 1) << 3) + x + 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + 1, y + 1, board));
        }
        if (board[((y + 1) << 3) + x - 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - 1, y + 1, board));
        }
        if (board[((y - 1) << 3) + x].color != Color::white) {
          moves.push_back(MovePiece(x, y, x, y - 1, board));
        }
        if (board[((y - 1) << 3) + x + 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x + 1, y - 1, board));
        }
        if (board[((y - 1) << 3) + x - 1].color != Color::white) {
          moves.push_back(MovePiece(x, y, x - 1, y - 1, board));
        }
        break;
      }
  }
}
