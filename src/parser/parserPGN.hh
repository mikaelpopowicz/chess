#ifndef PARSER_PGN_HH_
# define PARSER_PGN_HH_

# include <vector>
# include "../move.hh"
# include <iostream>
# include <fstream>

class ParserPGN
{
public:
  ParserPGN(std::string filename)
    : filename_(filename)
  {}
  ~ParserPGN();
  bool parse();
  std::vector<Move> get_white_move();
  std::vector<Move> get_black_move();

private:
  std::vector<Move> white_player_move_;
  std::vector<Move> black_player_move_;
  std::string filename_;
  Move get_move_from_string(std::string move);
};


#endif /* PARSER_PGN_HH_ */
