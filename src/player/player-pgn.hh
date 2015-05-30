#ifndef PLAYER_PGN_HH_
# define PLAYER_PGN_HH_

# include "player.hh"
# include "../color.hh"
# include "../move.hh"
# include "../piece-type.hh"
# include <vector>
# include <string>
# include "player-abstract.hh"

/*!
** \brief Chess manager (main)
*/
class PlayerPGN : public PlayerAbstract
{
public:
  PlayerPGN(Color color, std::vector<std::string> moves);
  ~PlayerPGN();

  /*!
  ** Set the last Move played by the opponent.
  */
  void last_opponent_move_set(const Move& last_opponent_move);

  /*!
  ** Return the next Move to be played by the Player.
  */
  Move move_get();

  void setMoves(std::vector<std::string> moves);
  void print();

private:
  std::vector<std::string> moves_;
  std::vector<std::string>::iterator iterator;

  Move little_rock();
  Move big_rock();
};

#endif /* !PLAYER_PGN_HH_ */