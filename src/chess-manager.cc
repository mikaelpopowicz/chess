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
        if (parse.isPGN())
        {
            ParserPGN parserPGN(parse.getFile());
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
    
}