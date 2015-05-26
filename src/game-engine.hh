#ifndef GAME_ENGINE_HH
# define GAME_ENGINE_HH

# include <vector>
# include "player.hh"
# include "observer.hh"
# include "chessboard.hh"

/*!
** \brief The game engine, which check moves, rules and play the game
*/
class GameEngine
{
public:
  GameEngine(Player p1, Player p2);
  virtual ~GameEngine();

  void set_observer(Observer o);
  /*!
  ** Play the game.
  ** @return 2 if a move is invalid, else 0
  */
  int play();

protected:
  /*!
  ** Represents the number of moves since:
  **   - no piece has been taken &
  **   - no pawn has been moved
  */
  int nb_turn_no_move_;
  /*!
  ** The current chessboard
  */
  Chessboard actual_;
  /*!
  ** This history is used to check for the threefold repetition
  ** (if the exact same configuration occurs three times).
  */
  std::vector<Chessboard> history_;

  bool check_move();
  bool check_rules();
  void add_history(Chessboard cb);
  void clear_history();
};

#endif /* !GAME_ENGINE_HH */
