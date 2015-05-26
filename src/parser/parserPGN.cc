#include "parserPGN.hh"

std::~ParserPGN()
{}

std::vector<Move> ParserPGN::get_black_move()
{
  return black_player_move_;
}

std::vector<Move> ParserPGN::get_white_move()
{
  return white_player_move_;
}

bool ParserPGN::parse()
{
  std::ifstream file("../../tests/examples/valid.out");
  if (!file)
    return false;

  std::string line;
  file >> line;
  while (line[0] != '1')
    file >> line;
  if (file.eof())
    return false;

  int nb_move = 0;
  int index = 0;
  //we get the move's number
  while (line[index] != '.')
    nb_move = nb_move * 10 + line[index++] - '0';
  while (line[index] == ' ' || line[index] == '\n')
    {
      index++;
      if (line[index] == '\n')
        {
          file >> line;
          index = 0;
        }
    }

  
/*
    skip headers

    get move number
    skip every spaces
    get white move
    skipo spaces
    get black move
    skip space
    repeat
   */

  return true;
}

Move get_move_from_string(std::string move)
{
  Move new_move;
  return new_move;
}
