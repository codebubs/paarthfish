#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <optional>
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
  int castle = 0;
  bool capture;
  PieceType promotion = PieceType::empty;

  Move(const int& f, const int& t, const bool& c)
      : from(f), to(t), capture(c) {}
  Move(const int& fx, const int& fy, const int& tx, const int& ty,
       const bool& c)
      : from((fy << 3) + fx), to((ty << 3) + tx), capture(c) {}
  Move(const int& fx, const int& fy, const int& tx, const int& ty,
       const bool& c, const PieceType& p)
      : from((fy << 3) + fx), to((ty << 3) + tx), capture(c), promotion(p) {}
  Move(const int& c) : castle(c) {}
};

using MoveList = std::vector<Move>;

class Board {
 public:
  PieceList piece_list;
  Color color;
  std::optional<Move> best_move;
  std::shared_ptr<Board> next, best_pos;
  bool wlc, wrc, blc, brc;
  Board(const PieceList& pl, Color c)
      : color(c), piece_list(pl), wlc(true), wrc(true), blc(true), brc(true) {}
  Board(const PieceList& pl, Color c, bool wlc, bool wrc, bool blc, bool brc)
      : color(c), piece_list(pl), wlc(wlc), wrc(wrc), blc(blc), brc(brc) {}
};

using BoardList = std::vector<Board>;
using BoardPointer = std::shared_ptr<Board>;

void MakeMove(BoardPointer board, const Move& move);
void DrawBoard(BoardPointer board);

void Movement(const int& n, BoardPointer board, MoveList& moves);
void Movement(const int& x, const int& y, BoardPointer b, MoveList& moves);