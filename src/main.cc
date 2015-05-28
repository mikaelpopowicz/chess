#include <iostream>
#include "chess-manager.hh"
#include "parser/option-parser.hh"

int main(int argc, char *argv[])
{
    ChessManager manager(argc, argv);
    return manager.go();
}
