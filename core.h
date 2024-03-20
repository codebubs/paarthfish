#pragma once
#include <array>
#include <iostream>
#include <vector>

enum class Color { black, white, none };
enum class PieceType { pawn, knight, bishop, rook, queen, king, empty };

struct Piece {
  Color color;
  PieceType type;
  int value;
  Piece(const Color& c, const PieceType& t) : color(c), type(t) {
    switch (t) {
      case PieceType::pawn:
        value = 1;
        break;
      case PieceType::knight:
        value = 3;
        break;
      case PieceType::bishop:
        value = 3;
        break;
      case PieceType::rook:
        value = 5;
        break;
      case PieceType::queen:
        value = 9;
        break;
      case PieceType::king:
        value = 1000;
        break;
      default:
        value = 0;
        break;
    }
  }
};

using PieceList = std::array<Piece, 64>;

class Move {
 public:
  unsigned int from, to;
  Move(const int& f, const int& t) : from(f), to(t) {}
  Move(const int& fx, const int& fy, const int& tx, const int& ty)
      : from((fy << 3) + fx), to((ty << 3) + tx) {}
};

using MoveList = std::vector<Move>;

class Board {
 public:
  PieceList pieceList;
  Board *previous, *next = nullptr;
  Board(const PieceList& pl) : pieceList(pl) {}
};

using BoardList = std::vector<Board>;

void MakeMove(Board& board, const Move& move);
void Undo(Board& board);

void DrawBoard(const PieceList& board);

void Movement(const int& n, const PieceList& board, MoveList& moves);
void Movement(const int& x, const int& y, const PieceList& board,
              MoveList& moves);