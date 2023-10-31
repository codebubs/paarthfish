#include "board.h"

int main() {
  Board board = {
      Piece('b', 'r'), Piece('b', 'n'), Piece('b', 'b'), Piece('b', 'q'),
      Piece('b', 'k'), Piece('b', 'b'), Piece('b', 'n'), Piece('b', 'r'),
      Piece('b', 'p'), Piece('b', 'p'), Piece('b', 'p'), Piece('b', 'p'),
      Piece('b', 'p'), Piece('b', 'p'), Piece('b', 'p'), Piece('b', 'r'),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '), Piece(' ', ' '),
      Piece('w', 'p'), Piece('w', 'p'), Piece('w', 'p'), Piece('w', 'p'),
      Piece('w', 'p'), Piece('w', 'p'), Piece('w', 'p'), Piece('w', 'p'),
      Piece('w', 'r'), Piece('w', 'n'), Piece('w', 'b'), Piece('w', 'q'),
      Piece('w', 'k'), Piece('w', 'b'), Piece('w', 'n'), Piece('w', 'r'),
  };
  Board newBoard = MovePiece(0, 0, 0, 4, board);
  DrawBoard(newBoard);

  return 0;
}