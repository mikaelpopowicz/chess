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
  /*!
  ** Make the move concerned.
  ** @return 0 if nothing exceptional happened (& move done)
  ** @return 1 if there is a promotion
  ** @return 2 if there's a kingside castling
  ** @return 3 if there's a queenside castling
  ** @return -1 if no move
  */
  int make_move(Move m);

  bool has_king_moved(Color c);
  Position get_king_pos(Color c);

  inline bool operator==(const Chessboard& chessboard) const;

protected:
  Piece board_[SIZE][SIZE];
  bool white_king_moved_;
  bool black_king_moved_;
  Position white_king_;
  Position black_king_;
};

# include "chessboard.hxx"

#endif /*! CHESSBOARD_HH */
