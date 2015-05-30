#include "player-pgn.hh"

PlayerPGN::PlayerPGN(Color color, std::vector<std::string> moves)
  : PlayerAbstract(color)
  , moves_(moves)
{
  iterator = moves_.begin();
}

PlayerPGN::~PlayerPGN()
{}

void PlayerPGN::last_opponent_move_set(const Move& last_opponent_move)
{
  Move test = last_opponent_move;
}

Move PlayerPGN::move_get()
{
  std::string = *iterator;
  iterator++;

  //Check if this is a rock
  if (raw_move[0] == 'O')
  {
    if (raw_move == "O-O")
    {
      return little_rock();
    }
    else
    {
      return big_rock();
    }
  }

  /**
  * Parse the raw move to get the position and the piece type
  * check all the possibility where the piece could come from
  * if there is one piece, this is the right one
  * else, return move()
  **/



  return Move();
}

void PlayerPGN::setMoves(std::vector<std::string> moves)
{
  this->moves_ = moves;
}

Move PlayerPGN::little_rock()
{
  if (color_ == Color::WHITE)
  {
    Position begin(Position::EVA, Position::EINS);
    Position end(Position::GUSTAV, Position::EINS);
    return move(begin, end, PieceType::KING);
  }
  else
  {
    Position begin(Position::EVA, Position::ACHT);
    Position end(Position::GUSTAV, Position::ACHT);
    return move(begin, end, PieceType::KING);
  }
}

Move PlayerPGN::big_rock()
{
  if (color_ == Color::WHITE)
  {
    Position begin(Position::EVA, Position::EINS);
    Position end(Position::CESAR, Position::EINS);
    return move(begin, end, PieceType::KING);
  }
  else
  {
    Position begin(Position::EVA, Position::ACHT);
    Position end(Position::CESAR, Position::ACHT);
    return move(begin, end, PieceType::KING);
  }
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