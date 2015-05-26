#ifndef CHESSBOARD_HH
# define CHESSBOARD_HH

# include "piece.hh"
# include "move.hh"
# include "position.hh"

#define SIZE 8

class Chessboard
{
public:
  Chessboard();
  virtual ~Chessboard();

  Piece get_piece_pos(Position p);
  Piece get_piece(Position::File f, Position::Rank r);
  bool make_move(Move m);

protected:
  Piece board_[SIZE][SIZE];
};

#endif /*! CHESSBOARD_HH */
