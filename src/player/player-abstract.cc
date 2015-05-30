#include "player-abstract.hh"

PlayerAbstract::PlayerAbstract(Color color)
  : Player(color)
{
  fileMap_["a"] = Position::ANNA;
  fileMap_["b"] = Position::BELLA;
  fileMap_["c"] = Position::CESAR;
  fileMap_["d"] = Position::DAVID;
  fileMap_["e"] = Position::EVA;
  fileMap_["f"] = Position::FELIX;
  fileMap_["g"] = Position::GUSTAV;
  fileMap_["h"] = Position::HECTOR;

  rankMap_["1"] = Position::EINS;
  rankMap_["2"] = Position::ZWEI;
  rankMap_["3"] = Position::DREI;
  rankMap_["4"] = Position::VIER;
  rankMap_["5"] = Position::FUNF;
  rankMap_["6"] = Position::SECHS;
  rankMap_["7"] = Position::SIEBEN;
  rankMap_["8"] = Position::ACHT;

  pieceMap_["K"] = PieceType::KING;
  pieceMap_["Q"] = PieceType::QUEEN;
  pieceMap_["R"] = PieceType::ROOK;
  pieceMap_["B"] = PieceType::BISHOP;
  pieceMap_["N"] = PieceType::KNIGHT;
  pieceMap_["P"] = PieceType::PAWN;
}

PlayerAbstract::~PlayerAbstract()
{
}