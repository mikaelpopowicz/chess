#include "parserPGN.hh"

ParserPGN::ParserPGN(std::string filename)
  : filename_(filename)
{}

ParserPGN::~ParserPGN()
{}

std::vector<std::string> ParserPGN::get_black_move()
{
  return black_player_move_;
}

std::vector<std::string> ParserPGN::get_white_move()
{
  return white_player_move_;
}

bool is_end_token(std::string token)
{
  return (token == "1-0" || token == "0-1" ||
          token == "1/2-1/2");
}

bool ParserPGN::parse()
{
  std::ifstream file(this->filename_);
  if (!file)
    return false;

  std::string token;
  file >> token;
  while ((token[0] != '1' || token[1] != '.') && !file.eof())
    file >> token;
  if (file.eof())
  {
    std::cerr << "Parser error: There is no move #1" << std::endl;
    return false;
  }

  int old_nb_move = 0;

  while (!file.eof())
    {
      int nb_move = 0;
      unsigned int index = 0;
      if (is_end_token(token))
        break;

      //we get the move's number
      while (token[index] != '.')
        nb_move = nb_move * 10 + token[index++] - '0';
      if (nb_move != old_nb_move + 1)
      {
        std::cerr << "Parser error: Wrong move number (`" << nb_move <<
          "` instead of `" << old_nb_move + 1 << "`)" << std::endl;
        return false;
      }

      if (token.length() == (++index))
        //There is a space between the move number and the first move
        {
          file >> token;
          index = 0;
        }

      std::string white_move = token.substr(index);
      std::string black_move;

      file >> black_move;
      bool is_the_end = false;
      if (is_end_token(white_move))
      {
        is_the_end = true;
      }
      else if (is_end_token(black_move))
      {
        is_the_end = true;
        white_player_move_.push_back(white_move);
      }
      else
      {
        white_player_move_.push_back(white_move);
        black_player_move_.push_back(black_move);
      }
      if (white_move == "*" || black_move == "*")
        is_the_end = true;

      if (is_the_end)
        break;
      old_nb_move = nb_move;
      file >> token;
    }
  return true;
}

Move ParserPGN::get_move_from_string(std::string move)
{
  move = move;
  return Move();
}
