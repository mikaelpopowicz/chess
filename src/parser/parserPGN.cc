#include "parserPGN.hh"

ParserPGN::ParserPGN(std::string filename)
  : filename_(filename)
{}

ParserPGN::~ParserPGN()
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
  std::string filename = "../../tests/examples/valid.out";
  std::ifstream file(filename);
  if (!file)
    return false;

  std::string token;
  file >> token;
  while (token[0] != '1' && !file.eof())
    file >> token;
  if (file.eof())
    return false;

  int nb_move = 0;
  unsigned int index = 0;
  //we get the move's number
  while (token[index] != '.')
    nb_move = nb_move * 10 + token[index++] - '0';

  if (token.length() == (++index))
    //There is a space between the move number and the first move
    {
      file >> token;
      index = 0;
    }

  std::string white_move = token.substr(index);
  std::string black_move;
  file >> black_move;
  std::cout << nb_move << "  White move: " << white_move << "  Black_move: " << black_move << std::endl;
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

Move ParserPGN::get_move_from_string(std::string move)
{
  move = move;
  Move new_move;
  return new_move;
}
