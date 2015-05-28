#ifndef CHESS_MANAGER_HH_
# define CHESS_MANAGER_HH_

# include <string>
# include <vector>
# include "player/player.hh"
# include "parser/parserPGN.hh"

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
  Player white_;
  Player black_;
  void createPGNplayers(ParserPGN parser)
};

#endif /* !CHESS_MANAGER_HH_ */