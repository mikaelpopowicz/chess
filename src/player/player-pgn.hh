#ifndef PLAYER_PGN_HH_
# define PLAYER_PGN_HH_

# include "player.hh"
# include "../color.hh"
# include "../move.hh"
# include "../piece-type.hh"

/*!
** \brief Chess manager (main)
*/
class PlayerPGN : public Player
{
public:
  PlayerPGN(Color color);
  ~PlayerPGN();
  
  /*!
  ** Set the last Move played by the opponent.
  */
  void last_opponent_move_set(const Move& last_opponent_move);

  /*!
  ** Return the next Move to be played by the Player.
  */
  Move move_get();

private:
  std::vector<std::string> moves_;
};

#endif /* !PLAYER_PGN_HH_ */