#ifndef OPTION_PARSER_HH_
# define OPTION_PARSER_HH_

# include <string>
# include <vector>

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
  bool isPgn();
  std::string getFile();
  std::vector<std::string> getLibs();
  void print();
  void printUsage();
  
private:
  int argc_;
  char **argv_;
  bool error_;
  bool pgn_;
  std::string file_;
  std::string player1_;
  std::string player2_;
  std::vector<std::string> libs_;

  void parsePlayer(std::string token);
  void parseLib(std::string token);
};

#endif /* !OPTION_PARSER_HH_ */