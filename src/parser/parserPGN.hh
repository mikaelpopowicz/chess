#ifndef PARSER_PGN_HH_
# define PARSER_PGN_HH_

# include <vector>
# include "../move.hh"
# include <iostream>

class ParserPGN
{
public:
  //Insert methods here
  ParserPGN();
  bool parse();
  std::vector<Move> get_white_moves();
  std::vector<Move> get_black_moves();

private:
  std::vector<Move> white_player_move_;
  std::vector<Move> black_player_move_;
  //Insert args here
};


#endif /* PARSER_PGN_HH_ */
