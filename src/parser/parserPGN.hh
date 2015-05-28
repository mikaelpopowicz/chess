#ifndef PARSER_PGN_HH_
# define PARSER_PGN_HH_

# include <vector>
# include "../move.hh"
# include <iostream>
# include <fstream>

class ParserPGN
{
public:
  ParserPGN(std::string filename);
  ~ParserPGN();
  bool parse();
  std::vector<std::string> get_white_move();
  std::vector<std::string> get_black_move();

private:
  std::vector<std::string> white_player_move_;
  std::vector<std::string> black_player_move_;
  std::string filename_;
  Move get_move_from_string(std::string move);
};


#endif /* PARSER_PGN_HH_ */
