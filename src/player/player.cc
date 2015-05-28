#include "player.hh"

Player::Player(Color color)
  : color_ (color)
{
}

Player::~Player()
{
}

Color Player::color_get() const
{
  return color_;
}

void Player::last_opponent_move_set(const Move& last_opponent_move)
{
  last_opponent_move_ = last_opponent_move;
}
