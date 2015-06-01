#ifndef CHESSBOARD_ADAPTER_HH
# define CHESSBOARD_ADAPTER_HH

# include "chessboard-interface.hh"
# include "chessboard.hh"

class ChessboardAdapter: public ChessboardInterface
{
public:
  ChessboardAdapter(Chessboard cb);
  std::pair<const PieceType, const Color> operator[]
    (const Position& position) const;

protected:
 Chessboard chessboard_;
};

#endif /*! CHESSBOARD_ADAPTER_HH */
