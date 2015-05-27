#include "chess-manager.hh"
#include "option-parser.hh"

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
        return 0;
    }
    else
    {
        opt.printUsage();
        return 1;
    }
}