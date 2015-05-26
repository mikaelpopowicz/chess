#ifndef OPTION_PARSER_HH_
# define OPTION_PARSER_HH_

# include <string>

/*!
** \brief Options parser
*/
class OptionParser
{
public:
  OptionParser(int argc, char *argv[]);
  ~OptionParser();
  
  /*!
  ** Parse the command line options
  ** @return bool If errors occured
  */
  bool parse();
  
  bool isPgn();
  std::string getFile();
  
private:
  int argc_;
  char *argv_[];
  bool pgn_;
  std::string file_;
  std::string player1_;
  std::string player2_;
};

#endif /* !OPTION_PARSER_HH_ */