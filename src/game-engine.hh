#ifndef GAME_ENGINE_HH
# define GAME_ENGINE_HH

# include <vector>
# include "player.hh"
# include "move.hh"
//# include "observer.hh"
# include "chessboard.hh"

/*!
** \brief The game engine, which check moves, rules and play the game
*/
class GameEngine
{
public:
  GameEngine(Player* p1, Player* p2);
  virtual ~GameEngine();

//  void set_observer(Observer o);
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
  int is_finished();

protected:
  Player* p1_;
  Player* p2_;
  Move actual_move_;
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
//  Observer observer_;
  /*!
  ** This history is used to check for the threefold repetition
  ** (if the exact same configuration occurs three times).
  */
  std::vector<Chessboard> history_;

  bool check_move(Move m);
  bool check_rules();
  void add_history(Chessboard cb);
  void clear_history();

  bool check_pawn_move(Move m, Piece p);
  bool check_rook_move(Move m);
  bool check_knight_move(Move m);
  bool check_bishop_move(Move m);
  bool check_king_move(Move m, Piece p);
};

#endif /*! GAME_ENGINE_HH */
