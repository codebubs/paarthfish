#include "board.h"
#include "pieces.h"

int main() {
  Board board = {
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
  };

  board[(2 << 3) + 4] = Piece(Color::white, PieceType::king);

  DrawBoard(board);

  MoveList moves;
  Movement(4, 2, board, moves);
  for (int i = 0; i < moves.size(); i++) {
    DrawBoard(moves[i]);
  }

  std::cout << '\n';

  return 0;
}