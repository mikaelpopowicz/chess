#include "parserPGN.hh"

std::vector<Move> ParserPGN::get_black_moves()
{
  return this->black_player_move_;
}

std::vector<Move> ParserPGN::get_white_moves()
{
  return this->white_player_move_;
}
