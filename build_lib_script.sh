g++ -Wextra -Werror -pedantic -std=c++1y -fPIC -shared src/pretty_printer_listener.cc src/listener.cc src/chessboard.cc src/move.cc src/position.cc -o lib_pretty_printer.so