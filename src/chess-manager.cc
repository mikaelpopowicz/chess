#include "chess-manager.hh"
#include "parser/option-parser.hh"
#include "game-engine.hh"

ChessManager::ChessManager(int argc, char **argv)
  : argc_(argc),
    argv_(argv)
{}

ChessManager::~ChessManager()
{
  if (this->white_ != NULL)
  {
    this->white_ = NULL;
    delete this->white_;
  }
  if (this->black_ != NULL)
  {
    this->black_ = NULL;
    delete this->black_;
  }
}

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
      if (opt.getWhitePlayer() == "human")
      {
        this->white_ = new PlayerHuman(Color::WHITE);
      }

      if (opt.getBlackPlayer() == "human")
        this->black_ = new PlayerHuman(Color::BLACK);
    }

    this->white_->print();
    this->black_->print();

/*    for (int i = 0; i < 20; i++)
    {
      Move move = this->black_->move_get();
      std::cout << move << std::endl;
    }*/

    GameEngine gm(white_, black_);
    gm.play();
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
  this->white_ = new PlayerPGN(Color::WHITE, parser.get_white_move());
  this->black_ = new PlayerPGN(Color::BLACK, parser.get_black_move());
}
