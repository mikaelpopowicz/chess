#include <iostream>
#include "chess-manager.hh"
#include "option-parser.hh"

int main(int argc, char *argv[])
{
    ChessManager manager(argc, argv);
    return manager.go();
}
