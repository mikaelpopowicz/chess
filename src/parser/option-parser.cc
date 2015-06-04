#include "option-parser.hh"

OptionParser::OptionParser(int argc, char **argv)
    : argc_(argc),
      argv_(argv),
      error_(false),
      pgn_(false),
      file_(""),
      player1_(""),
      player2_("")
{}

OptionParser::~OptionParser()
{}

bool OptionParser::parse()
{
    std::string token;
    int is_human_player = 0;
    for (int i(1); i < this->argc_; ++i)
    {
      token = std::string(this->argv_[i]);
      if (token.find("--") == 0)
        {
          is_human_player++;
          break;
        }
    }

    if (is_human_player > 0)
      return this->parse_player();
    return this->parse_pgn();
}

bool OptionParser::parse_pgn()
{
  std::string token(argv_[argc_ - 1]);
  this->file_ = token;
  for (int i = 1; i < argc_ - 1; i++)
    {
      token = std::string(argv_[i]);
      this->libs_.push_back(token);
    }
  pgn_ = true;
  return true;
}

bool OptionParser::is_pgn()
{
    return this->pgn_;
}

std::string OptionParser::get_file()
{
    return this->file_;
}

std::string OptionParser::get_white_player()
{
    return this->player1_;
}

std::string OptionParser::get_black_player()
{
  return this->player2_;
}

std::vector<std::string> OptionParser::get_libs()
{
  return this->libs_;
}

bool OptionParser::parse_player()
{
  std::string token;
  for (int i = 1; i < argc_; i++)
    {
      token = std::string(argv_[i]);
      if (token.find("--") == 0)
        {
          token = token.substr(2);
          std::string player;
          std::string::size_type count = token.find('=');
          if (count != std::string::npos)
            {
              player = token.substr(count + 1);
              if (player == "human"
                  || player.find(".so", player.length() - 4) != std::string::npos)
                {
                  if (token.substr(0, count) == "player-white")
                    {
                      if (this->player1_ == "")
                        this->player1_ = player;
                      else
                        return false;
                    }
                  else if (token.substr(0, count) == "player-black")
                    {
                      if (this->player2_ == "")
                        this->player2_ = player;
                      else
                        return false;
                    }
                  else
                    return false;
                }
              else
                return false;
            }
          else
            return false;
        }
      else
        this->libs_.push_back(token);
    }
  return true;
}

void OptionParser::print()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "Options : " << std::endl;
    std::cout << "Is PGN ?\t" << std::boolalpha << this->is_pgn() << std::endl;
    std::cout << "List of libs :" << std::endl;
    for (std::string st : this->libs_)
    {
        std::cout << "\t" << st << std::endl;
    }
    std::cout << "PGN file :\t" << this->file_ << std::endl;
    std::cout << "PLayer white:\t" << this->player1_ << std::endl;
    std::cout << "PLayer black:\t" << this->player2_ << std::endl;
}

void OptionParser::print_usage()
{
    std::string usage = "Usage: ./chess [--player-white=[human | *.so]";
    usage.append(" --player-black=[human | *.so ]] [*.so ...] [file.pgn]");
    std::cerr << usage << std::endl;
}
