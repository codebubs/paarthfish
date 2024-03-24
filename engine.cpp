#include "engine.h"

#include <thread>

#include "core.h"

using PSTable = std::array<int, 64>;

PSTable flip_table(const PSTable& table) {
  PSTable new_table;
  for (int i = 0; i < 64; i++) {
    new_table[i] = table[63 - i];
  }
  return new_table;
}

const PSTable pawn_table = {
    0,  0,  0,  0,   0,   0,  0,  0,  50, 50, 50,  50, 50, 50,  50, 50,
    10, 10, 20, 30,  30,  20, 10, 10, 5,  5,  10,  25, 25, 10,  5,  5,
    0,  0,  0,  20,  20,  0,  0,  0,  5,  -5, -10, 0,  0,  -10, -5, 5,
    5,  10, 10, -20, -20, 10, 10, 5,  0,  0,  0,   0,  0,  0,   0,  0};
const PSTable knight_table = {
    50,  -40, -30, -30, -30, -30, -40, -50, -40, -20, 0,   0,   0,
    0,   -20, -40, -30, 0,   10,  15,  15,  10,  0,   -30, -30, 5,
    15,  20,  20,  15,  5,   -30, -30, 0,   15,  20,  20,  15,  0,
    -30, -30, 5,   10,  15,  15,  10,  5,   -30, -40, -20, 0,   5,
    5,   0,   -20, -40, -50, -40, -30, -30, -30, -30, -40, -50};
const PSTable bishop_table = {
    -20, -10, -10, -10, -10, -10, -10, -20, -10, 0,   0,   0,   0,
    0,   0,   -10, -10, 0,   5,   10,  10,  5,   0,   -10, -10, 5,
    5,   10,  10,  5,   5,   -10, -10, 0,   10,  10,  10,  10,  0,
    -10, -10, 10,  10,  10,  10,  10,  10,  -10, -10, 5,   0,   0,
    0,   0,   5,   -10, -20, -10, -10, -10, -10, -10, -10, -20};
const PSTable rook_table = {0,  0,  0, 0,  0, 0,  0,  0, 5,  10, 10, 10, 10,
                            10, 10, 5, -5, 0, 0,  0,  0, 0,  0,  -5, -5, 0,
                            0,  0,  0, 0,  0, -5, -5, 0, 0,  0,  0,  0,  0,
                            -5, -5, 0, 0,  0, 0,  0,  0, -5, -5, 0,  0,  0,
                            0,  0,  0, -5, 0, 0,  0,  5, 5,  0,  0,  0};
const PSTable queen_table = {
    -20, -10, -10, -5, -5, -10, -10, -20, -10, 0,   0,   0,  0,  0,   0,   -10,
    -10, 0,   5,   5,  5,  5,   0,   -10, -5,  0,   5,   5,  5,  5,   0,   -5,
    0,   0,   5,   5,  5,  5,   0,   -5,  -10, 5,   5,   5,  5,  5,   0,   -10,
    -10, 0,   5,   0,  0,  0,   0,   -10, -20, -10, -10, -5, -5, -10, -10, -20};

const PSTable flipped_pawn_table = flip_table(pawn_table);
const PSTable flipped_knight_table = flip_table(knight_table);
const PSTable flipped_bishop_table = flip_table(bishop_table);
const PSTable flipped_rook_table = flip_table(rook_table);
const PSTable flipped_queen_table = flip_table(queen_table);

const unsigned int threads = std::thread::hardware_concurrency();

int Evaluate(const BoardPointer board) {
  int score = 0;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].type != PieceType::empty) {
      if (board->piece_list[i].color == Color::white) {
        switch (board->piece_list[i].type) {
          case PieceType::pawn:
            score += 100 + pawn_table[i];
            break;
          case PieceType::knight:
            score += 320 + knight_table[i];
            break;
          case PieceType::bishop:
            score += 330 + bishop_table[i];
            break;
          case PieceType::rook:
            score += 500 + rook_table[i];
            break;
          case PieceType::queen:
            score += 900 + queen_table[i];
            break;
          case PieceType::king:
            score += 20000;
            break;
        }
      } else if (board->piece_list[i].color == Color::black) {
        switch (board->piece_list[i].type) {
          case PieceType::pawn:
            score -= 100 + flipped_pawn_table[i];
            break;
          case PieceType::knight:
            score -= 320 + flipped_knight_table[i];
            break;
          case PieceType::bishop:
            score -= 330 + flipped_bishop_table[i];
            break;
          case PieceType::rook:
            score -= 500 + flipped_rook_table[i];
            break;
          case PieceType::queen:
            score -= 900 + flipped_queen_table[i];
            break;
          case PieceType::king:
            score -= 20000;
            break;
        }
      }
    }
  }
  return score + 28 * (board->color == Color::white ? 1 : -1);
}
int Quiesce(const int& ndepth, int alpha, const int& beta, BoardPointer board) {
  int score = Evaluate(board);
  if (score >= beta) return beta;
  if (ndepth == 0) return score;
  if (score > alpha) {
    alpha = score;
  }

  MoveList moves;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == board->color) {
      Movement(i, board->piece_list, moves);
    }
  }

  for (size_t i = 0; i < moves.size(); i++) {
    if (!moves[i].capture) continue;
    MakeMove(board, moves[i]);
    int score = -Quiesce(ndepth - 1, -beta, -alpha, board->next);

    if (score > alpha) {
      board->best_move = board->next;
      alpha = score;
    }
    if (score >= beta) return beta;
  }
  return alpha;
}

int NegaMax(int alpha, const int& beta, const int& depth, BoardPointer board) {
  if (depth == 0) {
    return Quiesce(4, alpha, beta, board);
  }
  MoveList moves;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == board->color) {
      Movement(i, board->piece_list, moves);
    }
  }

  for (size_t i = 0; i < moves.size(); i++) {
    MakeMove(board, moves[i]);

    int score = -NegaMax(-beta, -alpha, depth - 1, board->next);

    if (score > alpha) {
      alpha = score;
      board->best_move = board->next;
    }
    if (score >= beta) return beta;
  }
  return alpha;
}

int Engine(const int& depth, BoardPointer board) {
  MoveList moves;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == board->color) {
      Movement(i, board->piece_list, moves);
    }
  }

  unsigned int j = 0;
  int best_score = -100000;
  while (j < moves.size()) {
    const unsigned int t = __min(moves.size() - j, threads);
    for (size_t i = j; i < j + t; i++) {
      std::thread thread([&] {
        MakeMove(board, moves[i]);
        int score = -NegaMax(-100000, -best_score, depth - 1, board->next);

        if (score > best_score) {
          best_score = score;
          board->best_move = board->next;
        }
      });
      thread.join();
    }
    j += t;
  }
  return best_score;
}