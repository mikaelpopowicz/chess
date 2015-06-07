#include "awesome-ai.hh"

AwesomeAI::AwesomeAI(Color color)
  : color_(color)
{
  nb_move_ = 0;
}

AwesomeAI::~AwesomeAI()
{}

Move AwesomeAI::move_get()
{
  Move move;
  if (nb_move_ < 4 && color_ == Color::WHITE)
    move = make_white_opening();
  else if (nb_move_ < 4)
    move = make_black_opening();
  else
    move = minimax();
  nb_move_++;
  return move;
}

Move AwesomeAI::minimax()
{
  int nb_step = 4;
  /* TODO : RECURSIVE METHODES !!!! */
}

Move AwesomeAI::make_white_opening()
{
  switch (nb_move_)
  {
    case 0:
    {
      //Move the right knight
      Position begin(Position::GUSTAV, Position::EINS);
      Position end(Position::FELIX, Position::DREI);
      return Move(begin, end);
    }
    case 1:
    {
      //Move the Pawn in front of the king
      Position begin(Position::EVA, Position::ZWEI);
      Position end(Position::EVA, Position::DREI);
      return Move(begin, end);
    }
    case 2:
    {
      //Move the right bishop
      Position begin(Position::FELIX, Position::EINS);
      Position end(Position::DAVIDn Position::DREI);
      return Move(begin, end);
    }
    case 3:
    {
      //Little rock
      Position begin(Position::EVA, Position::EINS);
      Position end(Position::GUSTAV, Position::EINS);
      return Move(begin, end);
    }
    default:
    {
      return Move();
      break;
    }
  }
}

Move AwesomeAI::make_black_opening()
{
  switch (nb_move_)
  {
    case 0:
    {
      //Move the right knight
      Position begin(Position::GUSTAV, Position::ACHT);
      Position end(Position::FELIX, Position::SECHS);
      return Move(begin, end);
    }
    case 1:
    {
      //Move the Pawn in front of the king
      Position begin(Position::EVA, Position::ZWEI);
      Position end(Position::EVA, Position::SECHS);
      return Move(begin, end);
    }
    case 2:
    {
      //Move the right bishop
      Position begin(Position::FELIX, Position::ACHT);
      Position end(Position::DAVIDn Position::SECHS);
      return Move(begin, end);
    }
    case 3:
    {
      //Little rock
      Position begin(Position::EVA, Position::ACHT);
      Position end(Position::GUSTAV, Position::ACHT);
      return Move(begin, end);
    }
    default:
    {
      return Move();
      break;
    }
  }
}

const std::string& AwesomeAI::name_get()
{
  return "laubie_g";
}
