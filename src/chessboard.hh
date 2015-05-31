#ifndef CHESSBOARD_HH
# define CHESSBOARD_HH

# include "piece.hh"
# include "move.hh"
# include "position.hh"
# include <vector>

#define SIZE 8

class Chessboard
{
public:
  Chessboard();
  virtual ~Chessboard();

  Piece get_piece_pos(Position p);
  Piece get_piece(Position::File f, Position::Rank r);
  bool make_move(Move m);

  bool has_king_moved(Color c);

protected:
  Piece board_[SIZE][SIZE];
  bool white_king_moved_;
  bool black_king_moved_;
};

#endif /*! CHESSBOARD_HH */
