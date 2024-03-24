#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <vector>

enum class Color { black, white, none };
enum class PieceType { pawn, knight, bishop, rook, queen, king, empty };

struct Piece {
  Color color;
  PieceType type;
  Piece(const Color& c, const PieceType& t) : color(c), type(t) {}
};

using PieceList = std::array<Piece, 64>;

class Move {
 public:
  unsigned int from, to;
  bool capture;
  Move(const int& f, const int& t, const bool& c)
      : from(f), to(t), capture(c) {}
  Move(const int& fx, const int& fy, const int& tx, const int& ty,
       const bool& c)
      : from((fy << 3) + fx), to((ty << 3) + tx), capture(c) {}
};

using MoveList = std::vector<Move>;

class Board {
 public:
  PieceList piece_list;
  Color color;
  std::shared_ptr<Board> next, best_move;
  Board(const PieceList& pl, Color c) : color(c), piece_list(pl) {}
};

using BoardList = std::vector<Board>;
using BoardPointer = std::shared_ptr<Board>;

void MakeMove(BoardPointer board, const Move& move);

void DrawBoard(const PieceList& board);

void Movement(const int& n, const PieceList& board, MoveList& moves);
void Movement(const int& x, const int& y, const PieceList& board,
              MoveList& moves);