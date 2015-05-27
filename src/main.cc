#include <iostream>
#include "option-parser.hh"

int main(int argc, char *argv[])
{
    std::cout << "Hello toto!" << std::endl;
    OptionParser toto(argc, argv);
    if (toto.parse())
    {
        std::cout << "Parse ok" << std::endl;
    }
    else
    {
        std::cout << "Va te faire mettre !" << std::endl;
    }
    toto.print();

}
