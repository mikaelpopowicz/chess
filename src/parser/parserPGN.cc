#include "parserPGN.hh"

std::vector<Move> ParserPGN::get_black_move()
{
  return this->black_player_move_;
}

std::vector<Move> ParserPGN::get_white_move()
{
  return this->white_player_move_;
}

bool ParserPGN::parse()
{
  ifstream file = new ifstream(this->filename_);
  return true;
}
