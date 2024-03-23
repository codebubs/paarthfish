#include "core.h"

#include <array>
#include <iostream>
#include <vector>

void MakeMove(BoardPointer board, const Move& move) {
  Color color;
  if (board->color == Color::white) {
    color = Color::black;
  } else {
    color = Color::white;
  }
  board->next = BoardPointer(new Board(board->piece_list, color));
  board->next->piece_list[move.to] = board->next->piece_list[move.from];
  board->next->piece_list[move.from] = Piece(Color::none, PieceType::empty);
}

void DrawBoard(const PieceList& board) {
  std::cout << "\n   +---+---+---+---+---+---+---+---+\n";
  for (size_t i = 0; i < board.size(); i++) {
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

void Movement(const int& n, const PieceList& board, MoveList& moves) {
  return Movement(n & 7, n >> 3, board, moves);
}
void Movement(const int& x, const int& y, const PieceList& board,
              MoveList& moves) {
  switch (board[(y << 3) + x].type) {
    case PieceType::pawn:
      if (board[(y << 3) + x].color == Color::white) {
        if (y > 0) {
          if (board[((y - 1) << 3) + x].type == PieceType::empty) {
            moves.push_back(Move(x, y, x, y - 1));
          }
          if (board[((y - 1) << 3) + x - 1].color == Color::black) {
            moves.push_back(Move(x, y, x - 1, y - 1));
          }
          if (board[((y - 1) << 3) + x + 1].color == Color::black) {
            moves.push_back(Move(x, y, x + 1, y - 1));
          }
          if (y == 6) {
            if (board[((y - 2) << 3) + x].type == PieceType::empty) {
              moves.push_back(Move(x, y, x, y - 2));
            }
          }
        }
      } else {
        if (y < 7) {
          if (board[((y + 1) << 3) + x].type == PieceType::empty) {
            moves.push_back(Move(x, y, x, y + 1));
          }
          if (board[((y + 1) << 3) + x - 1].color == Color::white) {
            moves.push_back(Move(x, y, x - 1, y + 1));
          }
          if (board[((y + 1) << 3) + x + 1].color == Color::white) {
            moves.push_back(Move(x, y, x + 1, y + 1));
          }
          if (y == 1) {
            if (board[((y + 2) << 3) + x].type == PieceType::empty) {
              moves.push_back(Move(x, y, x, y + 2));
            }
          }
        }
      }
      break;
    case PieceType::knight:
      if (board[(y << 3) + x].color == Color::white) {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(Move(x, y, x + 2, y - 1));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(Move(x, y, x + 2, y + 1));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(Move(x, y, x - 2, y - 1));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(Move(x, y, x - 2, y + 1));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(Move(x, y, x - 1, y - 2));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(Move(x, y, x + 1, y - 2));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(Move(x, y, x - 1, y + 2));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(Move(x, y, x + 1, y + 2));
          }
        }
      } else {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(Move(x, y, x + 2, y - 1));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(Move(x, y, x + 2, y + 1));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(Move(x, y, x - 2, y - 1));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(Move(x, y, x - 2, y + 1));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(Move(x, y, x - 1, y - 2));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(Move(x, y, x + 1, y - 2));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(Move(x, y, x - 1, y + 2));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(Move(x, y, x + 1, y + 2));
          }
        }
      }
      break;
    case PieceType::bishop: {
      int i = 1;
      if (board[(y << 3) + i].color == Color::white) {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::white) {
          moves.push_back(Move(x, y, x + i, y + i));
          if (board[((y + i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y + i));
          if (board[((y + i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          moves.push_back(Move(x, y, x + i, y - i));
          if (board[((y - i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y - i));
          if (board[((y - i) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y + i));
          if (board[((y + i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y + i));
          if (board[((y + i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y - i));
          if (board[((y - i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y - i));
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
          moves.push_back(Move(x, y, x, y + i));
          if (board[((y + i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          moves.push_back(Move(x, y, x, y - i));
          if (board[((y - i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          moves.push_back(Move(x, y, x + i, y));
          if (board[((y) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y));
          if (board[((y) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          moves.push_back(Move(x, y, x, y + i));
          if (board[((y + i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          moves.push_back(Move(x, y, x, y - i));
          if (board[((y - i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y));
          if (board[((y) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y));
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
          moves.push_back(Move(x, y, x + i, y + i));
          if (board[((y + i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y + i));
          if (board[((y + i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          moves.push_back(Move(x, y, x + i, y - i));
          if (board[((y - i) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y - i));
          if (board[((y - i) << 3) + x - i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::white) {
          moves.push_back(Move(x, y, x, y + i));
          if (board[((y + i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          moves.push_back(Move(x, y, x, y - i));
          if (board[((y - i) << 3) + x].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          moves.push_back(Move(x, y, x + i, y));
          if (board[((y) << 3) + x + i].color == Color::black) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          moves.push_back(Move(x, y, x - i, y));
          if (board[((y) << 3) + x - i].color == Color::black) break;
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y + i));
          if (board[((y + i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y + i));
          if (board[((y + i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y - i));
          if (board[((y - i) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y - i));
          if (board[((y - i) << 3) + x - i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          moves.push_back(Move(x, y, x, y + i));
          if (board[((y + i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          moves.push_back(Move(x, y, x, y - i));
          if (board[((y - i) << 3) + x].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          moves.push_back(Move(x, y, x + i, y));
          if (board[((y) << 3) + x + i].color == Color::white) break;
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          moves.push_back(Move(x, y, x - i, y));
          if (board[((y) << 3) + x - i].color == Color::white) break;
          i++;
        }
      }
      break;
    }
    case PieceType::king:
      if (board[(y << 3) + x].color == Color::white) {
        if (board[(y << 3) + x + 1].color != Color::white) {
          moves.push_back(Move(x, y, x + 1, y));
        }
        if (board[(y << 3) + x - 1].color != Color::white) {
          moves.push_back(Move(x, y, x - 1, y));
        }
        if (y != 7) {
          if (board[((y + 1) << 3) + x].color != Color::white) {
            moves.push_back(Move(x, y, x, y + 1));
          }
          if (board[((y + 1) << 3) + x + 1].color != Color::white) {
            moves.push_back(Move(x, y, x + 1, y + 1));
          }
          if (board[((y + 1) << 3) + x - 1].color != Color::white) {
            moves.push_back(Move(x, y, x - 1, y + 1));
          }
        }
        if (y != 0) {
          if (board[((y - 1) << 3) + x].color != Color::white) {
            moves.push_back(Move(x, y, x, y - 1));
          }
          if (board[((y - 1) << 3) + x + 1].color != Color::white) {
            moves.push_back(Move(x, y, x + 1, y - 1));
          }
          if (board[((y - 1) << 3) + x - 1].color != Color::white) {
            moves.push_back(Move(x, y, x - 1, y - 1));
          }
        }
        break;
      }
  }
}
