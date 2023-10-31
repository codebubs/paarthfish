#pragma once
#include <array>
#include <iostream>

struct Piece {
  char color;
  char type;
  Piece(const char& c, const char& t) : color(c), type(t) {}
};
using Board = std::array<Piece, 64>;

Piece GetPiece(const size_t& x, const size_t& y, const Board& board);

Board MovePiece(const size_t& px, const size_t& py, const size_t& nx,
                const size_t& ny, Board board);

void DrawBoard(const Board& board);