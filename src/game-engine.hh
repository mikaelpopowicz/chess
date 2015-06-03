#ifndef GAME_ENGINE_HH_
# define GAME_ENGINE_HH_

# include <vector>
# include "player/player.hh"
# include "move.hh"
# include "observer.hh"
# include "chessboard.hh"

/*!
** \brief The game engine, which check moves, rules and play the game
*/
class GameEngine
{
public:
  GameEngine(Player* p1, Player* p2, Observer o);
  virtual ~GameEngine();

  /*!
  ** Play the game.
  ** @return 2 if a move is invalid, else 0
  */
  int play();
  /*!
  ** Check if the game is finished
  ** @return 0 if the game is not finished, 1 if the player White won,
  ** @return 2 if the player black won, 3 if nobody won
  */
  int is_finished(Color c);

protected:
  Player* p1_;
  Player* p2_;
  Observer observer_;
  Move actual_move_;
  Position previous_moved_;
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

  void add_history(Chessboard cb);
  void clear_history();
};

#endif /*! GAME_ENGINE_HH_ */
