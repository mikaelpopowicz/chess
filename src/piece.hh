#ifndef PIECE_HH
# define PIECE_HH

# include "piece-type.hh"
# include "color.hh"

class Piece
{
public:
  Piece();
  Piece(PieceType pt, Color c);
  virtual ~Piece();

  PieceType get_type();
  void set_type(PieceType pt);
  Color get_color();
  void set_color(Color c);

protected:
  PieceType piece_type_;
  Color color_;
};

#endif /*! PIECE_HH */
