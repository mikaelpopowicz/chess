#ifndef OPTION_PARSER_HH_
# define OPTION_PARSER_HH_

# include <string>
# include <vector>
# include <iostream>

/*!
** \brief Options parser
*/
class OptionParser
{
public:
  OptionParser(int argc, char **argv);
  ~OptionParser();

  /*!
  ** Parse the command line options
  ** @return bool If errors occured
  */
  bool parse();
  bool is_pgn();
  std::string get_file();
  std::string get_white_player();
  std::string get_black_player();
  std::vector<std::string> get_libs();
  void print();
  void print_usage();

private:
  int argc_;
  char **argv_;
  bool error_;
  bool pgn_;
  std::string file_;
  std::string player1_;
  std::string player2_;
  std::vector<std::string> libs_;

  bool parse_player();
  bool parse_pgn();
};

#endif /* !OPTION_PARSER_HH_ */
