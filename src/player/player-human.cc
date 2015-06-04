#include "player-human.hh"

PlayerHuman::PlayerHuman(Color color)
  : PlayerAbstract(color)
{}

PlayerHuman::~PlayerHuman()
{}

Move PlayerHuman::move_get()
{
  std::string col(color_ == Color::WHITE ? "white" : "black");
  std::cout << "Please player " << col << " enter your move (e.g. a6Nc7) :" << std::endl;
  std::string humanMove;
  std::cin >> humanMove;
  Position pos_null = Position(Position::FILE_FIRST, Position::RANK_FIRST);
  if (humanMove.length() == 5)
  {
    std::string initial = humanMove.substr(0, 2);
    std::string piece = humanMove.substr(2, 1);
    std::string end = humanMove.substr(3, 2);
    if (!this->checkPosition(initial) || !this->checkPiece(piece)
      || !this->checkPosition(end))
      return Move(pos_null, pos_null);
    Position initialPos(this->fileMap_[initial.substr(0, 1)],
      this->rankMap_[initial.substr(1, 1)]);
    Position endPos(this->fileMap_[end.substr(0, 1)],
      this->rankMap_[end.substr(1, 1)]);
    return Move(initialPos, endPos);
  }
  return Move(pos_null, pos_null);
}

bool PlayerHuman::checkPosition(std::string position)
{
  if (this->fileMap_[position.substr(0, 1)] == 0)
    return false;
  if (this->rankMap_[position.substr(1,1)] == 0)
    return false;
  return true;
}

bool PlayerHuman::checkPiece(std::string piece)
{
  if (this->pieceMap_[piece] == 0 && piece != "K")
    return false;
  return true;
}

void PlayerHuman::print()
{
  std::cout << "I'm human !" << std::endl;
}
