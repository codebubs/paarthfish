#include "engine.h"

#include <iostream>

#include "core.h"

int Evaluate(const PieceList& board) {
  int score = 0;
  for (int i = 0; i < 64; i++) {
    if (board[i].type != PieceType::empty) {
      if (board[i].color == Color::black) {
        score -= board[i].value;
      } else if (board[i].color == Color::white) {
        score += board[i].value;
      }
    }
  }
  return score;
}
int NegaMax(int alpha, const int& beta, const int& depth, Board& board) {
  if (depth == 0) return Evaluate(board.pieceList);
  MoveList moves;
  for (int i = 0; i < 64; i++) {
    if (board.pieceList[i].type != PieceType::empty) {
      Movement(i, board.pieceList, moves);
    }
  }

  for (int i = 0; i < moves.size(); i++) {
    MakeMove(board, moves[i]);
    int score = -NegaMax(-beta, -alpha, depth - 1, board);
    Undo(board);
    if (score >= beta) return beta;
    if (score > alpha) {
      alpha = score;
    }
  }
  std::cout << "hello";
  return alpha;
}
