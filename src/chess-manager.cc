#include "chess-manager.hh"
#include "parser/option-parser.hh"

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
      this->white_->print();
      this->black_->print();
    }
    else
    {
      if (opt.getWhitePlayer() == "human")
      {
        this->white_ = new PlayerHuman(Color::WHITE);
        std::cout << this->white_->move_get() << std::endl;
      }

      if (opt.getBlackPlayer() == "human")
        this->black_ = new PlayerHuman(Color::BLACK);
    }

    this->white_->print();
    this->black_->print();
    this->white_->move_get();
    this->white_->move_get();
    this->white_->move_get();
    this->white_->move_get();
    this->white_->move_get();
    this->white_->move_get();
    this->white_->move_get();

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