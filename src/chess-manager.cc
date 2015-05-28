#include "chess-manager.hh"
#include "parser/option-parser.hh"

ChessManager::ChessManager(int argc, char **argv)
  : argc_(argc),
    argv_(argv)
{}

ChessManager::~ChessManager()
{}

int ChessManager::go()
{
  OptionParser opt(this->argc_, this->argv_);
  if (opt.parse())
  {
    if (opt.isPgn())
    {
      ParserPGN parserPGN(opt.getFile());
      if (parserPGN.parse())
        createPGNplayers(parserPGN);
      else
        return 2;
    }
    else
    {
    }
    return 0;
  }
  else
  {
    opt.printUsage();
    return 1;
  }
}


void ChessManager::createPGNplayers(ParserPGN parser)
{
  PlayerPGN *white = new PlayerPGN(Color::WHITE, parser.get_white_move());
  PlayerPGN *black = new PlayerPGN(Color::BLACK, parser.get_black_move());
  this->players_.push_back(white);
  this->players_.push_back(black);
}