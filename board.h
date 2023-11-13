#pragma once
#include <array>
#include <iostream>

enum class Color { black, white, none };
enum class PieceType { pawn, knight, bishop, rook, queen, king, empty };

struct Piece {
  Color color;
  PieceType type;
  Piece(const Color& c, const PieceType& t) : color(c), type(t) {}
};

class Move {
 public:
  unsigned int from, to, flags;
  Move(const int& f, const int& t, const int& g) : from(f), to(t), flags(g) {}
  bool IsPromotion();
  bool IsCapture();
  bool Special0();
  bool Special1();

  static unsigned int CreateFlags(const bool& capture, const bool& promotion,
                                  const bool& special0, const bool& special1);
};

using Board = std::array<Piece, 64>;

Board MovePiece(const int& px, const int& py, const int& nx, const int& ny,
                Board board);

void DrawBoard(const Board& board);