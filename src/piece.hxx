inline bool Piece::operator==(const Piece& piece) const
{
  return piece_type_ == piece.piece_type_ && color_ == piece.color_;
}

inline bool Piece::operator!=(const Piece& piece) const
{
  return !operator== (piece);
}
