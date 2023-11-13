#pragma once
#include "board.h"
#include "vector"

using MoveList = std::vector<Board>;
void Movement(const int& x, const int& y, const Board& board,
              MoveList& moves);