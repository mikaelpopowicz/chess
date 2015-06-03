#ifndef CHESS_MANAGER_HH_
# define CHESS_MANAGER_HH_

# include <string>
# include <vector>
# include "player/player.hh"
# include "player/player-pgn.hh"
# include "player/player-human.hh"
# include "parser/parserPGN.hh"
# include "parser/option-parser.hh"
# include "class-loader.hh"
# include "observer.hh"
# include "game-engine.hh"

/*!
** \brief Chess manager (main)
*/
class ChessManager
{
public:
  ChessManager(int argc, char **argv);
  ~ChessManager();

  /*!
  ** Parse the command line options
  ** @return bool If errors occured
  */
  int go();

private:
  int argc_;
  char **argv_;
  Player *white_;
  Player *black_;
  void create_pgn_players(ParserPGN parser);
};

#endif /* !CHESS_MANAGER_HH_ */
