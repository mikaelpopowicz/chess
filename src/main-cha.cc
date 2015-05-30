#include <iostream>

#include "piece.hh"
#include "piece-type.hh"
#include "color.hh"
#include "chessboard.hh"
#include "position.hh"
#include "game-engine.hh"

int main()
{
  std::cout << "king: " << KING << std::endl;
  std::cout << "QUEEN: " << QUEEN << std::endl;
  std::cout << "rook: " << ROOK << std::endl;
  std::cout << "BISHOP: " << BISHOP  << std::endl;
  std::cout << "KNIGHT: " << KNIGHT  << std::endl;
  std::cout << "PAWN: " << PAWN  << std::endl;
  std::cout << "NONE: " << NONE << std::endl;

  std::cout << "white: " << WHITE << std::endl;

  GameEngine gm(NULL, NULL);
  gm.play();


}
