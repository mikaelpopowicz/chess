#ifndef CHESSBOARD_INTERFACE_HH_
# define CHESSBOARD_INTERFACE_HH_

# include "color.hh"
# include "piece-type.hh"
# include "position.hh"

/*!
** \brief interface of the chessboard.
**
** this class should be the mother class of the adapter.
*/
class ChessboardInterface
{
public:
  virtual ~ChessboardInterface();

  /*!
  ** Acces operator.
  **
  ** @param position A position on the chessboard.
  */
  virtual std::pair<const PieceType, const Color>
  operator[](const Position& position) const = 0;
};

#endif /* !CHESSBOARD_INTERFACE_HH_ */
