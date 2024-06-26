#include "core.h"

void MakeMove(BoardPointer board, const Move& move) {
  Color color;
  if (board->color == Color::white) {
    color = Color::black;
  } else {
    color = Color::white;
  }

  board->next = BoardPointer(new Board(board->piece_list, color, board->wlc,
                                       board->wrc, board->blc, board->brc));
  if (move.castle == 1) {
    if (board->color == Color::white) {
      board->next->piece_list[62] = board->next->piece_list[60];
      board->next->piece_list[61] = board->next->piece_list[63];
      board->next->piece_list[60] = Piece(Color::none, PieceType::empty);
      board->next->piece_list[63] = Piece(Color::none, PieceType::empty);
      board->next->wlc = false;
      board->next->wrc = false;
    } else {
      board->next->piece_list[6] = board->next->piece_list[4];
      board->next->piece_list[5] = board->next->piece_list[7];
      board->next->piece_list[4] = Piece(Color::none, PieceType::empty);
      board->next->piece_list[7] = Piece(Color::none, PieceType::empty);
      board->next->blc = false;
      board->next->brc = false;
    }
  } else if (move.castle == -1) {
    if (board->color == Color::white) {
      board->next->piece_list[58] = board->next->piece_list[60];
      board->next->piece_list[59] = board->next->piece_list[56];
      board->next->piece_list[60] = Piece(Color::none, PieceType::empty);
      board->next->piece_list[56] = Piece(Color::none, PieceType::empty);
      board->next->wlc = false;
      board->next->wrc = false;
    } else {
      board->next->piece_list[2] = board->next->piece_list[4];
      board->next->piece_list[3] = board->next->piece_list[0];
      board->next->piece_list[4] = Piece(Color::none, PieceType::empty);
      board->next->piece_list[0] = Piece(Color::none, PieceType::empty);
      board->next->piece_list[7] = Piece(Color::none, PieceType::empty);
      board->next->blc = false;
      board->next->brc = false;
    }
  } else {
    if (board->piece_list[move.from].type == PieceType::king) {
      if (board->color == Color::white) {
        board->next->wlc = false;
        board->next->wrc = false;
      } else {
        board->next->blc = false;
        board->next->brc = false;
      }
    }
    if (move.from == 56 || move.to == 56) board->next->wlc = false;
    if (move.from == 63 || move.to == 63) board->next->wrc = false;
    if (move.from == 0 || move.to == 0) board->next->blc = false;
    if (move.from == 7 || move.to == 7) board->next->brc = false;
    if (move.promotion != PieceType::empty) {
      board->next->piece_list[move.to] = Piece(board->color, move.promotion);
    } else {
      board->next->piece_list[move.to] = board->next->piece_list[move.from];
    }
    board->next->piece_list[move.from] = Piece(Color::none, PieceType::empty);
  }
  board->next->previous = board;
}

bool InCheck(const int& k, BoardPointer board) {
  Color c = board->color == Color::white ? Color::black : Color::white;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == c) {
      MoveList moves;
      Movement(i, board, moves, false);
      for (int j = 0; j < moves.size(); j++) {
        if (moves[j].to == k) {
          return true;
        }
      }
    }
  }
  return false;
}

void Movement(const int& n, BoardPointer board, MoveList& moves) {
  return Movement(n & 7, n >> 3, board, moves, true);
}
void Movement(const int& n, BoardPointer board, MoveList& moves, bool special) {
  return Movement(n & 7, n >> 3, board, moves, special);
}
void Movement(const int& x, const int& y, BoardPointer board, MoveList& moves) {
  return Movement(x, y, board, moves, true);
}
void Movement(const int& x, const int& y, BoardPointer b, MoveList& moves,
              bool special) {
  const PieceList& board = b->piece_list;
  switch (board[(y << 3) + x].type) {
    case PieceType::pawn:
      if (board[(y << 3) + x].color == Color::white) {
        if (y > 0) {
          if (y == 1 && special) {
            for (int i = 1; i < 5; i++) {
              if (board[((y - 1) << 3) + x].type == PieceType::empty) {
                moves.push_back(Move(x, y, x, y - 1, false, (PieceType)i));
              }
              if (x > 0 &&
                  board[((y - 1) << 3) + x - 1].color == Color::black) {
                moves.push_back(Move(x, y, x - 1, y - 1, true, (PieceType)i));
              }
              if (x < 7 &&
                  board[((y - 1) << 3) + x + 1].color == Color::black) {
                moves.push_back(Move(x, y, x + 1, y - 1, true, (PieceType)i));
              }
            }
          } else {
            if (board[((y - 1) << 3) + x].type == PieceType::empty) {
              moves.push_back(Move(x, y, x, y - 1, false));
            }
            if (x > 0 && board[((y - 1) << 3) + x - 1].color == Color::black) {
              moves.push_back(Move(x, y, x - 1, y - 1, true));
            }
            if (x < 7 && board[((y - 1) << 3) + x + 1].color == Color::black) {
              moves.push_back(Move(x, y, x + 1, y - 1, true));
            }
            if (y == 6) {
              if (board[((y - 2) << 3) + x].type == PieceType::empty &&
                  board[((y - 1) << 3) + x].type == PieceType::empty) {
                moves.push_back(Move(x, y, x, y - 2, false));
              }
            }
          }
        }
      } else {
        if (y < 7) {
          if (y == 6 && special) {
            for (int i = 1; i < 5; i++) {
              if (board[((y + 1) << 3) + x].type == PieceType::empty) {
                moves.push_back(Move(x, y, x, y + 1, false, (PieceType)i));
              }
              if (x > 0 &&
                  board[((y + 1) << 3) + x - 1].color == Color::white) {
                moves.push_back(Move(x, y, x - 1, y + 1, true, (PieceType)i));
              }
              if (x < 7 &&
                  board[((y + 1) << 3) + x + 1].color == Color::white) {
                moves.push_back(Move(x, y, x + 1, y + 1, true, (PieceType)i));
              }
            }
          } else {
            if (board[((y + 1) << 3) + x].type == PieceType::empty) {
              moves.push_back(Move(x, y, x, y + 1, false));
            }
            if (x > 0 && board[((y + 1) << 3) + x - 1].color == Color::white) {
              moves.push_back(Move(x, y, x - 1, y + 1, true));
            }
            if (x < 7 && board[((y + 1) << 3) + x + 1].color == Color::white) {
              moves.push_back(Move(x, y, x + 1, y + 1, true));
            }
            if (y == 1) {
              if (board[((y + 2) << 3) + x].type == PieceType::empty &&
                  board[((y + 1) << 3) + x].type == PieceType::empty) {
                moves.push_back(Move(x, y, x, y + 2, false));
              }
            }
          }
        }
      }
      break;
    case PieceType::knight:
      if (board[(y << 3) + x].color == Color::white) {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 2, y - 1,
                     board[((y - 1) << 3) + x + 2].color == Color::black));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 2, y + 1,
                     board[((y + 1) << 3) + x + 2].color == Color::black));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 2, y - 1,
                     board[((y - 1) << 3) + x - 2].color == Color::black));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 2, y + 1,
                     board[((y + 1) << 3) + x - 2].color == Color::black));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 1, y - 2,
                     board[((y - 2) << 3) + x - 1].color == Color::black));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 1, y - 2,
                     board[((y - 2) << 3) + x + 1].color == Color::black));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 1, y + 2,
                     board[((y + 2) << 3) + x - 1].color == Color::black));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 1, y + 2,
                     board[((y + 2) << 3) + x + 1].color == Color::black));
          }
        }
      } else {
        if (x <= 5) {
          if (y != 0 && board[((y - 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(
                Move(x, y, x + 2, y - 1,
                     board[((y - 1) << 3) + x + 2].color == Color::white));
          }
          if (y != 7 && board[((y + 1) << 3) + x + 2].color != Color::black) {
            moves.push_back(
                Move(x, y, x + 2, y + 1,
                     board[((y + 1) << 3) + x + 2].color == Color::white));
          }
        }
        if (x >= 2) {
          if (y != 0 && board[((y - 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(
                Move(x, y, x - 2, y - 1,
                     board[((y - 1) << 3) + x - 2].color == Color::white));
          }
          if (y != 7 && board[((y + 1) << 3) + x - 2].color != Color::black) {
            moves.push_back(
                Move(x, y, x - 2, y + 1,
                     board[((y + 1) << 3) + x - 2].color == Color::white));
          }
        }
        if (y >= 2) {
          if (x != 0 && board[((y - 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(
                Move(x, y, x - 1, y - 2,
                     board[((y - 2) << 3) + x - 1].color == Color::white));
          }
          if (x != 7 && board[((y - 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(
                Move(x, y, x + 1, y - 2,
                     board[((y - 2) << 3) + x + 1].color == Color::white));
          }
        }
        if (y <= 5) {
          if (x != 0 && board[((y + 2) << 3) + x - 1].color != Color::black) {
            moves.push_back(
                Move(x, y, x - 1, y + 2,
                     board[((y + 2) << 3) + x - 1].color == Color::white));
          }
          if (x != 7 && board[((y + 2) << 3) + x + 1].color != Color::black) {
            moves.push_back(
                Move(x, y, x + 1, y + 2,
                     board[((y + 2) << 3) + x + 1].color == Color::white));
          }
        }
      }
      break;
    case PieceType::bishop: {
      int i = 1;
      if (board[(y << 3) + x].color == Color::white) {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::white) {
          if (board[((y + i) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y + i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          if (board[((y + i) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y + i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          if (board[((y - i) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y - i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          if (board[((y - i) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y - i, false));
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          if (board[((y + i) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y + i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          if (board[((y + i) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y + i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          if (board[((y - i) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y - i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          if (board[((y - i) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y - i, false));
          i++;
        }
      }
      break;
    }
    case PieceType::rook: {
      int i = 1;
      if (board[(y << 3) + x].color == Color::white) {
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::white) {
          if (board[((y + i) << 3) + x].color == Color::black) {
            moves.push_back(Move(x, y, x, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y + i, false));
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          if (board[((y - i) << 3) + x].color == Color::black) {
            moves.push_back(Move(x, y, x, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y - i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          if (board[((y) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          if (board[((y) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y, false));
          i++;
        }
      } else {
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          if (board[((y + i) << 3) + x].color == Color::white) {
            moves.push_back(Move(x, y, x, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y + i, false));
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          if (board[((y - i) << 3) + x].color == Color::white) {
            moves.push_back(Move(x, y, x, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y - i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          if (board[((y) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          if (board[((y) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y, false));
          i++;
        }
      }
      break;
    }
    case PieceType::queen: {
      int i = 1;
      if (board[(y << 3) + x].color == Color::white) {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::white) {
          if (board[((y + i) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y + i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::white) {
          if (board[((y + i) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y + i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::white) {
          if (board[((y - i) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y - i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::white) {
          if (board[((y - i) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y - i, false));
          i++;
        }
        i = 1;
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::white) {
          if (board[((y + i) << 3) + x].color == Color::black) {
            moves.push_back(Move(x, y, x, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y + i, false));
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::white) {
          if (board[((y - i) << 3) + x].color == Color::black) {
            moves.push_back(Move(x, y, x, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y - i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::white) {
          if (board[((y) << 3) + x + i].color == Color::black) {
            moves.push_back(Move(x, y, x + i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::white) {
          if (board[((y) << 3) + x - i].color == Color::black) {
            moves.push_back(Move(x, y, x - i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y, false));
          i++;
        }
      } else {
        while (x + i <= 7 && y + i <= 7 &&
               board[((y + i) << 3) + x + i].color != Color::black) {
          if (board[((y + i) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y + i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y + i <= 7 &&
               board[((y + i) << 3) + x - i].color != Color::black) {
          if (board[((y + i) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y + i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && y - i >= 0 &&
               board[((y - i) << 3) + x + i].color != Color::black) {
          if (board[((y - i) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y - i, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && y - i >= 0 &&
               board[((y - i) << 3) + x - i].color != Color::black) {
          if (board[((y - i) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y - i, false));
          i++;
        }
        i = 1;
        while (y + i <= 7 && board[((y + i) << 3) + x].color != Color::black) {
          if (board[((y + i) << 3) + x].color == Color::white) {
            moves.push_back(Move(x, y, x, y + i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y + i, false));
          i++;
        }
        i = 1;
        while (y - i >= 0 && board[((y - i) << 3) + x].color != Color::black) {
          if (board[((y - i) << 3) + x].color == Color::white) {
            moves.push_back(Move(x, y, x, y - i, true));
            break;
          }
          moves.push_back(Move(x, y, x, y - i, false));
          i++;
        }
        i = 1;
        while (x + i <= 7 && board[((y) << 3) + x + i].color != Color::black) {
          if (board[((y) << 3) + x + i].color == Color::white) {
            moves.push_back(Move(x, y, x + i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x + i, y, false));
          i++;
        }
        i = 1;
        while (x - i >= 0 && board[((y) << 3) + x - i].color != Color::black) {
          if (board[((y) << 3) + x - i].color == Color::white) {
            moves.push_back(Move(x, y, x - i, y, true));
            break;
          }
          moves.push_back(Move(x, y, x - i, y, false));
          i++;
        }
      }
      break;
    }
    case PieceType::king: {
      if (board[(y << 3) + x].color == Color::white) {
        if (x != 7 && board[(y << 3) + x + 1].color != Color::white) {
          moves.push_back(Move(x, y, x + 1, y,
                               board[(y << 3) + x + 1].color == Color::black));
        }
        if (x != 0 && board[(y << 3) + x - 1].color != Color::white) {
          moves.push_back(Move(x, y, x - 1, y,
                               board[(y << 3) + x - 1].color == Color::black));
        }
        if (y != 7) {
          if (board[((y + 1) << 3) + x].color != Color::white) {
            moves.push_back(
                Move(x, y, x, y + 1,
                     board[((y + 1) << 3) + x].color == Color::black));
          }
          if (x != 7 && board[((y + 1) << 3) + x + 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 1, y + 1,
                     board[((y + 1) << 3) + x + 1].color == Color::black));
          }
          if (x != 0 && board[((y + 1) << 3) + x - 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 1, y + 1,
                     board[((y + 1) << 3) + x - 1].color == Color::black));
          }
        }
        if (y != 0) {
          if (board[((y - 1) << 3) + x].color != Color::white) {
            moves.push_back(
                Move(x, y, x, y - 1,
                     board[((y - 1) << 3) + x].color == Color::black));
          }
          if (x != 7 && board[((y - 1) << 3) + x + 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x + 1, y - 1,
                     board[((y - 1) << 3) + x + 1].color == Color::black));
          }
          if (x != 0 && board[((y - 1) << 3) + x - 1].color != Color::white) {
            moves.push_back(
                Move(x, y, x - 1, y - 1,
                     board[((y - 1) << 3) + x - 1].color == Color::black));
          }
        }
        if (special && (b->wlc || b->wrc) && !InCheck(60, b)) {
          if (b->wlc && board[57].type == PieceType::empty &&
              board[58].type == PieceType::empty && !InCheck(58, b) &&
              board[59].type == PieceType::empty && !InCheck(59, b)) {
            moves.push_back(Move(-1));
          }
          if (b->wrc && board[62].type == PieceType::empty && !InCheck(62, b) &&
              board[61].type == PieceType::empty && !InCheck(61, b)) {
            moves.push_back(Move(1));
          }
        }
      } else {
        if (board[(y << 3) + x].color == Color::black) {
          if (x != 7 && board[(y << 3) + x + 1].color != Color::black) {
            moves.push_back(Move(
                x, y, x + 1, y, board[(y << 3) + x + 1].color == Color::white));
          }
          if (x != 0 && board[(y << 3) + x - 1].color != Color::black) {
            moves.push_back(Move(
                x, y, x - 1, y, board[(y << 3) + x - 1].color == Color::white));
          }
          if (y != 7) {
            if (board[((y + 1) << 3) + x].color != Color::black) {
              moves.push_back(
                  Move(x, y, x, y + 1,
                       board[((y + 1) << 3) + x].color == Color::white));
            }
            if (x != 7 && board[((y + 1) << 3) + x + 1].color != Color::black) {
              moves.push_back(
                  Move(x, y, x + 1, y + 1,
                       board[((y + 1) << 3) + x + 1].color == Color::white));
            }
            if (x != 0 && board[((y + 1) << 3) + x - 1].color != Color::black) {
              moves.push_back(
                  Move(x, y, x - 1, y + 1,
                       board[((y + 1) << 3) + x - 1].color == Color::white));
            }
          }
          if (y != 0) {
            if (board[((y - 1) << 3) + x].color != Color::black) {
              moves.push_back(
                  Move(x, y, x, y - 1,
                       board[((y - 1) << 3) + x].color == Color::white));
            }
            if (x != 7 && board[((y - 1) << 3) + x + 1].color != Color::black) {
              moves.push_back(
                  Move(x, y, x + 1, y - 1,
                       board[((y - 1) << 3) + x + 1].color == Color::white));
            }
            if (x != 0 && board[((y - 1) << 3) + x - 1].color != Color::black) {
              moves.push_back(
                  Move(x, y, x - 1, y - 1,
                       board[((y - 1) << 3) + x - 1].color == Color::white));
            }
          }
          if (special && (b->blc || b->brc) && !InCheck(4, b)) {
            if (b->blc && board[1].type == PieceType::empty &&
                board[2].type == PieceType::empty && !InCheck(2, b) &&
                board[3].type == PieceType::empty && !InCheck(3, b)) {
              moves.push_back(Move(-1));
            }
            if (b->brc && board[5].type == PieceType::empty && !InCheck(5, b) &&
                board[6].type == PieceType::empty && !InCheck(6, b)) {
              moves.push_back(Move(1));
            }
          }
        }
      }
      break;
    }
  }
}

void DrawBoard(BoardPointer board) {
  std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
  for (size_t i = 0; i < board->piece_list.size(); i++) {
    char letter;
    switch (board->piece_list[i].type) {
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
    if (board->piece_list[i].color == Color::white) {
      std::cout << "| " << (char)toupper(letter) << " ";
    } else {
      std::cout << "| " << letter << " ";
    }
    if ((i & 7u) == 7u) {
      std::cout << "|" << std::endl
                << "   +---+---+---+---+---+---+---+---+" << std::endl;
    }
  }
  std::cout << "     a   b   c   d   e   f   g   h" << std::endl;
  std::cout << board->wlc << board->wrc << board->blc << board->brc
            << std::endl;
  int sq;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].type == PieceType::king &&
        board->piece_list[i].color == Color::white) {
      sq = i;
      break;
    }
  }
  std::cout << InCheck(sq, board) << std::endl;
}