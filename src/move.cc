#include <iostream>

#include "move.hh"

Move::Move ()
{
}

Move::Move(const Position& initial, const Position& final, PieceType promotion)
  : initial_ (initial),
    final_ (final),
    promotion_ (promotion)
{
}

const Position& Move::start_get() const
{
  return initial_;
}

const Position& Move::end_get() const
{
  return final_;
}

PieceType Move::promotion_get() const
{
  return promotion_;
}
