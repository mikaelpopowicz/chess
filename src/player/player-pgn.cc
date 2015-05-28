#include "player-pgn.hh"

PlayerPGN::PlayerPGN(Color color, std::vector<std::string> moves)
  : Player(color)
  , moves_(moves)
{}

PlayerPGN::~PlayerPGN()
{}

void PlayerPGN::last_opponent_move_set(const Move& last_opponent_move)
{
  Move test = last_opponent_move;
}

Move PlayerPGN::move_get()
{
  return Move();
}
void PlayerPGN::setMoves(std::vector<std::string> moves)
{
  this->moves_ = moves;
}