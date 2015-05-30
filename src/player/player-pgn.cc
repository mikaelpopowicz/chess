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

void PlayerPGN::print()
{
  std::cout << "=======================" << std::endl;
  std::cout << "==== player  print ====" << std::endl;
  if (this->color_ == Color::WHITE)
    std::cout << "White player" << std::endl;
  else if (this->color_ == Color::BLACK)
    std::cout << "Black player" << std::endl;

  int i(1);
  for (std::string st : this->moves_)
  {
    std::cout << "Move " << i << " : " << st << std::endl;
    ++i;
  }
  std::cout << "=======================" << std::endl;
}