#include "chess-manager.hh"

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
  Observer obs;
  ClassLoader loader;
  if (opt.parse())
  {
    if (opt.is_pgn())
    {
      ParserPGN parserPGN(opt.get_file());
      if (parserPGN.parse())
        create_pgn_players(parserPGN);
      else
        return 2;
    }
    else
    {
      if (opt.get_white_player() == "human")
      {
        this->white_ = new PlayerHuman(Color::WHITE);
      }
      else
      {
        if (!(this->white_ = loader.get_ia(opt.get_white_player(), Color::WHITE)))
          return 69;
      }

      if (opt.get_black_player() == "human")
        this->black_ = new PlayerHuman(Color::BLACK);
      else
      {
        if (!(this->black_ = loader.get_ia(opt.get_black_player(), Color::BLACK)))
          return 69;
      }
    }

    if (opt.get_libs().size() > 0)
    {
      if (loader.load_libraries(opt.get_libs()))
      {
        for (ListenerExport* plugin : loader.get_plugins())
        {
          Listener* toAdd = plugin->create();
          obs.add_observer(toAdd);
        }
      }
      else
        return 69;
    }
    GameEngine gm(white_, black_, obs);
    return gm.play();

  }
  else
  {
    opt.print_usage();
    return 1;
  }
}


void ChessManager::create_pgn_players(ParserPGN parser)
{
  this->white_ = new PlayerPGN(Color::WHITE, parser.get_white_move());
  this->black_ = new PlayerPGN(Color::BLACK, parser.get_black_move());
}
