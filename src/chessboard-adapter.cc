#include "chessboard-adapter.hh"
#include <utility>
#include <type_traits>

ChessboardAdapter::ChessboardAdapter(Chessboard cb)
  : chessboard_(cb)
{
}

std::pair<const PieceType, const Color> ChessboardAdapter::operator[]
  (const Position& position) const
{
  Piece p = chessboard_.get_piece_pos(position);
  return std::make_pair(p.get_type(), p.get_color());
}
