#ifndef PLAYER_ABSTRACT_HH_
# define PLAYER_ABSTRACT_HH_

# include <map>
# include <string>
# include "player.hh"

class PlayerAbstract : public Player
{
public:
  PlayerAbstract(Color color);
  ~PlayerAbstract();
protected:
  std::map<std::string, Position::File> fileMap_;
  std::map<std::string, Position::Rank> rankMap_;
  std::map<std::string, PieceType> pieceMap_;
};

#endif /* PLAYER_ABSTRACT_HH_ */