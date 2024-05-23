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
  bool engine_enabled = true;
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
    if (board->color == engine && engine_enabled) {
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
      std::string cmd;
      int f, t;
      std::optional<Move> move;
      std::cout << "Command: ";
      std::cin >> cmd;
      for (char& c : cmd) c = tolower(c);
      if (cmd.find_first_not_of('a') == std::string::npos) {
        BoardPointer last_board = board;
        int i = 0;
        while (true) {
          last_board = last_board->previous;
          if (!last_board) {
            std::cout << "Cannot go back " << cmd.size() << " times"
                      << std::endl;
            system("pause");
            break;
          } else if (++i == cmd.size()) {
            board = last_board;
            break;
          }
        }
        system("cls");
        continue;
      } else if (cmd.find_first_not_of('d') == std::string::npos) {
        BoardPointer last_board = board;
        int i = 0;
        while (true) {
          last_board = last_board->next;
          if (!last_board) {
            std::cout << "Cannot go forward " << cmd.size() << " times"
                      << std::endl;
            system("pause");
            break;
          } else if (++i == cmd.size()) {
            board = last_board;
            break;
          }
        }
        system("cls");
        continue;
      } else if (cmd == "disable") {
        engine_enabled = false;
        std::cout << "Disabled engine" << std::endl;
        system("pause");
        system("cls");
        continue;
      } else if (cmd == "enable") {
        engine_enabled = true;
        std::cout << "Enabled engine" << std::endl;
        system("pause");
        system("cls");
        continue;
      } else if (cmd == "help") {
        system("cls");
        std::cout
            << "Usage:" << std::endl
            << "a/d:     Go back/forward respectively. Type characters"
            << std::endl
            << "         on the same line to go back that many half-moves"
            << std::endl
            << "         (e.g. \"aaa\" to go back 3 half-moves)." << std::endl
            << "disable: Disable the engine" << std::endl
            << "enable:  Enable the engine" << std::endl
            << "o-o:     Castle short." << std::endl
            << "o-o-o:   Castle long." << std::endl
            << "Move:    To move, type the starting and ending square for the "
            << std::endl
            << "        move (e.g. \"e2e4\" to move the piece at e2 to e4)."
            << std::endl;
        system("pause");
        system("cls");
        continue;
      } else if (cmd == "o-o") {
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
      } else if (cmd == "o-o-o") {
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
      } else if (cmd.length() == 4) {
        f = (cmd[0] - 'a') + 8 * (7 - (cmd[1] - '1'));
        t = (cmd[2] - 'a') + 8 * (7 - (cmd[3] - '1'));
        if (f < 0 || f > 63 || t < 0 || t > 63) {
          std::cout << "Invalid move" << std::endl;
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
      } else {
        std::cout << "Invalid command" << std::endl
                  << "Type \"help\" for help" << std::endl;
        continue;
      }
      system("cls");
      MakeMove(board, move.value());
      game.push_back(move.value());
    }
    board = board->next;
  }
  return 0;
}
