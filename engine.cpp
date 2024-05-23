#include "engine.h"

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

int Evaluate(const BoardPointer board) {
  int score = 0;
  int pieces = 0;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].type != PieceType::empty) {
      if (board->piece_list[i].color == Color::white) {
        switch (board->piece_list[i].type) {
          case PieceType::pawn:
            score += 100 + pawn_table[i];
            pieces++;
            break;
          case PieceType::knight:
            score += 320 + knight_table[i];
            pieces++;
            break;
          case PieceType::bishop:
            score += 330 + bishop_table[i];
            pieces++;
            break;
          case PieceType::rook:
            score += 500 + rook_table[i];
            pieces++;
            break;
          case PieceType::queen:
            score += 900 + queen_table[i];
            pieces++;
            break;
          case PieceType::king:
            score += 20000;
            pieces++;
            break;
        }
      } else if (board->piece_list[i].color == Color::black) {
        switch (board->piece_list[i].type) {
          case PieceType::pawn:
            score -= 100 + flipped_pawn_table[i];
            pieces++;
            break;
          case PieceType::knight:
            score -= 320 + flipped_knight_table[i];
            pieces++;
            break;
          case PieceType::bishop:
            score -= 330 + flipped_bishop_table[i];
            pieces++;
            break;
          case PieceType::rook:
            score -= 500 + flipped_rook_table[i];
            pieces++;
            break;
          case PieceType::queen:
            score -= 900 + flipped_queen_table[i];
            pieces++;
            break;
          case PieceType::king:
            score -= 20000;
            pieces++;
            break;
        }
      }
    }
  }
  if (board->wlc) score += 35;
  if (board->wrc) score += 45;
  if (board->blc) score -= 35;
  if (board->brc) score -= 45;
  // score += 4 * (16 - pieces);
  return (score + 28) * (board->color == Color::white ? 1 : -1);
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
      Movement(i, board, moves);
    }
  }

  for (size_t i = 0; i < moves.size(); i++) {
    if (!moves[i].capture) continue;
    MakeMove(board, moves[i]);
    int score = -Quiesce(ndepth - 1, -beta, -alpha, board->next);

    if (score > alpha) {
      board->best_pos = board->next;
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

  int eval = Evaluate(board);
  if (eval < -10000) return -100000;
  if (eval > 10000) return 100000;

  MoveList moves;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == board->color) {
      Movement(i, board, moves);
    }
  }

  for (size_t i = 0; i < moves.size(); i++) {
    MakeMove(board, moves[i]);
    int score = -NegaMax(-beta, -alpha, depth - 1, board->next);

    if (score >= beta) return beta;
    if (score > alpha) {
      alpha = score;
      board->best_pos = board->next;
      board->best_move = moves[i];
    }
  }
  if (alpha > 69420) return alpha - 1;
  if (alpha < -69420) return alpha + 1;
  return alpha;
}

int Engine(const int& depth, BoardPointer board) {
  MoveList o_moves;
  for (int i = 0; i < 64; i++) {
    if (board->piece_list[i].color == board->color) {
      Movement(i, board, o_moves);
    }
  }

  std::cout << "0%";
  std::optional<Move> best_move;
  int last_score;
  for (int d = 4; d < depth; d++) {
    MoveList moves;
    if (best_move.has_value()) {
      for (size_t j = 0; j < o_moves.size(); j++) {
        if (o_moves[j].from != best_move.value().from ||
            o_moves[j].to != best_move.value().to) {
          moves.push_back(o_moves[j]);
        } else {
          moves.insert(moves.begin(), best_move.value());
        }
      }
    } else {
      moves = o_moves;
      for (size_t j = 0; j < o_moves.size(); j++) {
        MakeMove(board, o_moves[j]);
      }
    }
    int best_score = -100000;
    for (int i = 0; i < moves.size(); i++) {
      MakeMove(board, moves[i]);
      int score = -NegaMax(-100000, -best_score, d - 1, board->next);
      if (score > best_score) {
        best_score = score;
        board->best_pos = board->next;
        best_move = moves[i];
        board->best_move = moves[i];
      }
      std::cout << "Depth: " << d + 1
                << std::string(5 - (int)log10((double)d), ' ')
                << round(
                       (double(d) - 4.0 + (double(i) / double(moves.size()))) /
                       double(depth - 4) * 1000.0) /
                       10.0
                << "%      \r";
    }
    last_score = best_score;
  }
  return last_score;
}