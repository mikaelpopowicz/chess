#ifndef PLAYER_HUMAN_HH_
# define PLAYER_HUMAN_HH_

# include "player-abstract.hh"
# include "../color.hh"
# include "../move.hh"
# include "../piece-type.hh"
# include "../position.hh"
# include <map>
# include <iostream>
# include <string>

/*!
** \brief Chess manager (main)
*/
class PlayerHuman : public PlayerAbstract
{
public:
  PlayerHuman(Color color);
  ~PlayerHuman();

  /*!
  ** Return the next Move to be played by the Player.
  */
  Move move_get();

  bool checkPosition(std::string position);
  bool checkPiece(std::string piece);

  void print();
};

#endif /* !PLAYER_HUMAN_HH_ */




