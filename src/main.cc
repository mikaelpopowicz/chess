#include <iostream>

#include "piece.hh"
#include "piece-type.hh"
#include "color.hh"
#include "chessboard.hh"
#include "position.hh"

int main()
{
    Piece p(QUEEN, WHITE);
    std::cout << "Hello toto!" << std::endl;
    std::cout << p.get_type() << ":" << p.get_color() << ":" << std::endl;
    Chessboard* cb = new Chessboard();
    Position pos(Position::ANNA, Position::EINS);
    std::cout << ROOK << std::endl;
    std::cout << cb->get_piece_pos(pos).get_type() << std::endl;
    
    std::cout << WHITE << std::endl;
    std::cout << cb->get_piece_pos(pos).get_color() << std::endl;
/*    for (Position::File i = Position::ANNA; i < Position::FILE_LAST; ++i)
      for (Position::Rank j = Position::EINS; j < Position::RANK_LAST; ++j)
      {
        std::cout << cb->get_piece(j, i).get_type() << " ";
      }
    std::cout << std::endl;*/
}
