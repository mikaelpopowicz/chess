#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "color.hh"
# include "move.hh"
# include "piece-type.hh"

/*!
** \brief Highest player representation.
*/
class Player
{
public:
  Player(Color color);
  virtual ~Player();

  /*!
  ** Set the last Move played by the opponent.
  */
  virtual void last_opponent_move_set(const Move& last_opponent_move);

  /*!
  ** Return the next Move to be played by the Player.
  */
  virtual Move move_get() = 0;

  Color color_get() const;

protected:
  Color color_;
  Move last_opponent_move_;
};

#endif /* !PLAYER_HH_ */
