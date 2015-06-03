#ifndef PIECE_HH_
# define PIECE_HH_

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

  inline bool operator==(const Piece& piece) const;
  inline bool operator!=(const Piece& piece) const;

protected:
  PieceType piece_type_;
  Color color_;
};

# include "piece.hxx"

#endif /*! PIECE_HH_ */
