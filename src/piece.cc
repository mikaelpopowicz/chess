#include "piece.hh"
#include "piece-type.hh"
#include "color.hh"

Piece::Piece()
  : piece_type_ (NONE),
    color_ (BLACK)
{
}

Piece::Piece(PieceType pt, Color c)
  : piece_type_ (pt),
    color_ (c)
{
}

Piece::~Piece()
{
}

PieceType Piece::get_type()
{
  return this->piece_type_;
}

void Piece::set_type(PieceType pt)
{
  this->piece_type_ = pt;
}

Color Piece::get_color()
{
  return this->color_;
}

void Piece::set_color(Color c)
{
  this->color_ = c;
}
