#pragma once
#include "core.h"

int Evaluate(const PieceList& board);
int NegaMax(int alpha, const int& beta, const int& depth, Board* board);