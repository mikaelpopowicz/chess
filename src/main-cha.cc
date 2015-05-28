#include <iostream>

#include "piece.hh"
#include "piece-type.hh"
#include "color.hh"
#include "chessboard.hh"
#include "position.hh"

void printcb(Chessboard cb)
{
  for (int row = 0; row < 8; ++row)
  {
    for (int col = 0; col < 8; ++col)
    {
      Piece p = cb.get_piece(static_cast<Position::File>(col + 1), static_cast<Position::Rank>(row + 1));
      std::cout << "[" << p.get_type() << ";";
      std::cout << p.get_color() << "] ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main()
{
    Chessboard cb;
    std::cout << "king: " << KING << std::endl;
    std::cout << "QUEEN: " << QUEEN << std::endl;
    std::cout << "rook: " << ROOK << std::endl;
    std::cout << "BISHOP: " << BISHOP  << std::endl;
    std::cout << "KNIGHT: " << KNIGHT  << std::endl;
    std::cout << "PAWN: " << PAWN  << std::endl;
    std::cout << "NONE: " << NONE << std::endl;
    
    std::cout << "white: " << WHITE << std::endl;
  
    printcb(cb);

  Position p1(Position::EVA, Position::ACHT);
  Position p2(Position::GUSTAV, Position::ACHT);
  Position p3(Position::CESAR, Position::ACHT);
  Move m_kscastling(p1, p2);
  Move m_qscastling(p1, p3);
//  Move m(p1, p1);
  cb.make_move(m_kscastling);
//  cb.make_move(m);


  printcb(cb);
  cb.make_move(m_qscastling);
  printcb(cb);
}
