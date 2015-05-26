#ifndef LISTENER_HH_
# define LISTENER_HH_

# include <string>

# include "color.hh"
# include "piece-type.hh"
# include "position.hh"

class ChessboardInterface;

/*!
** \brief Listener interface.
**
** A listener is a part of the Observer design pattern.
*/
class Listener
{
public:
  virtual ~Listener();

  /*!
  ** \brief Register the ChessboardInterface for later use.
  ** Called once per game at the beginning.
  **
  ** @param chessboard_interface: The chessboard interface
  */
  virtual void register_chessboard_interface(const ChessboardInterface&
                                             chessboard_interface) = 0;

  /*!
  ** \brief Event when the game starts.
  */
  virtual void on_game_started() = 0;

  /*!
  ** \brief Event when the game finishes.
  ** No more event happens after it.
  */
  virtual void on_game_finished() = 0;

  /*!
  ** \brief Event when a piece is moved.
  **
  ** @param piece: The moving piece.
  ** @param from:  The initial position of the piece.
  ** @param to:    The final position of the piece.
  */
  virtual void on_piece_moved(const PieceType& piece, const Position& from,
                              const Position& to) = 0;

  /*!
  ** \brief Event when a piece is taken.
  **
  ** @param piece: The taken piece.
  ** @param at:    The position where the piece is taken.
  */
  virtual void on_piece_taken(const PieceType& piece, const Position& at) = 0;

  /*!
  ** \brief Event when a piece is promoted.
  **
  ** @param piece: The chosen type of piece of the promotion.
  ** @param at:    The position of the piece promoted.
  */
  virtual void on_piece_promoted(const PieceType& piece, const Position& p) = 0;

  /*!
  ** \brief Event when a Kingside castling happens.
  **
  ** @param color: The color of the player concerned by the castling.
  */
  virtual void on_kingside_castling(const Color& color) = 0;

  /*!
  ** \brief Event when a Queenside castling happens
  **
  ** @param color: The color of the player concerned by the castling
  */
  virtual void on_queenside_castling(const Color& color) = 0;

  /*!
  ** \brief Event when a King is in check.
  **
  ** Called after the move that put the King in check.
  ** @param color: The color of the player whose King is in check
  */
  virtual void on_player_check(const Color& color) = 0;

  /*!
  ** \brief Event when a King is checkmate.
  **
  ** Called after the move that made it checkmate
  ** @param color: The color of the player whose King is checkmate
  */
  virtual void on_player_mat(const Color& color) = 0;

  /*!
  ** \brief Event when a player is pat.
  **
  ** Called after the move that made it pat.
  ** @param color: The color of the player who is pat.
  */
  virtual void on_player_pat(const Color& color) = 0;

  /*!
  ** \brief Event when a player timed out.
  **
  ** @param color: The color of the player who timed out.
  */
  virtual void on_player_timeout(const Color& color) = 0;

  /*!
  ** \brief Event when a player is disqualified.
  **
  ** @param color: The color of the player who is disqualified.
  */
  virtual void on_player_disqualified(const Color& color) = 0;

  /*!
  ** \brief Event when there is a draw game.
  */
  virtual void on_draw() = 0;
};

struct ListenerExport
{
  Listener* (*create) ();
  std::string name;
};

# define LISTENER_EXPORT(NAME, NEW)             \
  static Listener* listener_create()	        \
  {						\
    return NEW;					\
  }						\
                                                \
  ListenerExport listener_plugin =              \
  {	                                        \
    listener_create,				\
    NAME 					\
  }

#endif /* !LISTENER_HH_ */
