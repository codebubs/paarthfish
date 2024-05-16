#include <chrono>
#include <thread>

#include "core.h"
#include "engine.h"

int main() {
  BoardPointer board = BoardPointer(new Board(
      {
          Piece(Color::black, PieceType::rook),
          Piece(Color::black, PieceType::knight),
          Piece(Color::black, PieceType::bishop),
          Piece(Color::black, PieceType::queen),
          Piece(Color::black, PieceType::king),
          Piece(Color::black, PieceType::bishop),
          Piece(Color::black, PieceType::knight),
          Piece(Color::black, PieceType::rook),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::black, PieceType::pawn),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::none, PieceType::empty),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::pawn),
          Piece(Color::white, PieceType::rook),
          Piece(Color::white, PieceType::knight),
          Piece(Color::white, PieceType::bishop),
          Piece(Color::white, PieceType::queen),
          Piece(Color::white, PieceType::king),
          Piece(Color::white, PieceType::bishop),
          Piece(Color::white, PieceType::knight),
          Piece(Color::white, PieceType::rook),
      },
      Color::white));

  int depth = 8;
  int color;
  Color engine = Color::none;
  std::cout << "Depth: ";
  std::cin >> depth;
  std::cout << "You play white (0) or black (1): ";
  std::cin >> color;
  engine = (Color)color;

  MoveList game;
  system("cls");
  while (true) {
    std::cout << std::endl;
    DrawBoard(board);
    std::cout << std::endl;
    if (board->color == engine) {
      const int& eval = Engine(depth, board);
      system("cls");
      std::cout << "Evaluation: " << eval * (engine == Color::white ? 1 : -1)
                << (eval * (engine == Color::white ? 1 : -1) > 10000
                        ? " (white wins)"
                    : eval * (engine == Color::white ? 1 : -1) < -10000
                        ? " (black wins)"
                        : "")
                << "         " << std::endl
                << "Line:" << std::endl;
      BoardPointer last_board = board;
      if (!last_board->best_move.has_value() || abs(eval) == 100000) {
        std::cout << std::endl;
        DrawBoard(board->best_pos);
        std::cout << std::endl << "Game over!" << std::endl;
        system("pause");
        exit(0);
      }
      while (last_board->best_move.has_value()) {
        if (last_board->best_move->castle == 1) {
          std::cout << "O-O" << std::endl;
        } else if (last_board->best_move->castle == -1) {
          std::cout << "O-O-O" << std::endl;
        } else {
          std::cout << (char)('a' + last_board->best_move->from % 8)
                    << (8 - (last_board->best_move->from >> 3)) << " to "
                    << (char)('a' + last_board->best_move->to % 8)
                    << (8 - (last_board->best_move->to >> 3));
          if (last_board->best_move->promotion == PieceType::empty) {
            std::cout << std::endl;
          } else {
            std::cout
                << " (promote to "
                << (last_board->best_move->promotion == PieceType::knight ? "N"
                    : last_board->best_move->promotion == PieceType::bishop
                        ? "B"
                    : last_board->best_move->promotion == PieceType::rook  ? "R"
                    : last_board->best_move->promotion == PieceType::queen ? "Q"
                                                                           : "")
                << ")" << std::endl;
          }
        }
        last_board = last_board->best_pos;
      }
      MakeMove(board, board->best_move.value());
      game.push_back(board->best_move.value());
    } else {
      std::string from, to;
      int f, t;
      std::optional<Move> move;
      std::cout << "Move: ";
      std::cin >> from;
      for (char& c : from) c = tolower(c);
      if (from == "o-o") {
        MoveList possible_moves;
        Movement(board->color == Color::white ? 60 : 4, board, possible_moves);
        for (int i = 0; i < possible_moves.size(); i++) {
          if (possible_moves[i].castle == 1) {
            move = possible_moves[i];
            break;
          }
        }
        if (!move.has_value()) {
          std::cout << "Invalid move" << std::endl;
          continue;
        }
      } else if (from == "o-o-o") {
        MoveList possible_moves;
        Movement(board->color == Color::white ? 60 : 4, board, possible_moves);
        for (int i = 0; i < possible_moves.size(); i++) {
          if (possible_moves[i].castle == -1) {
            move = possible_moves[i];
            break;
          }
        }
        if (!move.has_value()) {
          std::cout << "Invalid move" << std::endl;
          continue;
        }
      } else {
        std::cout << "To: ";
        std::cin >> to;
        for (char& c : to) c = tolower(c);
        f = (from[0] - 'a') + 8 * (7 - (from[1] - '1'));
        t = (to[0] - 'a') + 8 * (7 - (to[1] - '1'));
        if (from.length() != 2 || to.length() != 2 || f < 0 || f > 63 ||
            t < 0 || t > 63) {
          std::cout << "Invalid input" << std::endl;
          continue;
        }
        MoveList possible_moves;
        Movement(f, board, possible_moves);
        for (int i = 0; i < possible_moves.size(); i++) {
          if (possible_moves[i].to == t) {
            move = possible_moves[i];
            break;
          }
        }
        if (!move.has_value()) {
          std::cout << "Invalid move" << std::endl;
          continue;
        }
        if (move->promotion != PieceType::empty) {
          char promotion_char;
          PieceType promotion_piece;
          while (true) {
            std::cout << "Promotion piece (n, b, r, q): ";
            std::cin >> promotion_char;
            promotion_char = tolower(promotion_char);
            if (promotion_char == 'n') {
              promotion_piece = PieceType::knight;
            } else if (promotion_char == 'b') {
              promotion_piece = PieceType::bishop;
            } else if (promotion_char == 'r') {
              promotion_piece = PieceType::rook;
            } else if (promotion_char == 'q') {
              promotion_piece = PieceType::queen;
            } else {
              std::cout << "Invalid piece" << std::endl;
              continue;
            }
            break;
          }
          move->promotion = promotion_piece;
        }
      }
      system("cls");
      MakeMove(board, move.value());
      game.push_back(move.value());
    }
    board = board->next;
  }
  return 0;
}
