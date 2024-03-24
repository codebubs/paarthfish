#include <iostream>

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

  std::cout << "Paarthfish v0.1.0" << std::endl;
  std::cout << "Evaluation: " << Engine(8, board) << std::endl;
  BoardPointer last_board = board;
  while (true) {
    if (!last_board->best_move) break;
    last_board = last_board->best_move;
    DrawBoard(last_board->piece_list);
  }
  system("pause");
  return 0;
}