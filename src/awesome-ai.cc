#include "awesome-ai.hh"
#include <climits>
#include <vector>

AwesomeAi::AwesomeAi(Color color)
{
  color_ = color;
  nb_move_ = 0;
  name_ = "laubie_g";
}

AwesomeAi::~AwesomeAi()
{}

Move AwesomeAi::move_get()
{
  Move move;
  if (nb_move_ < 4 && color_ == Color::WHITE)
    move = make_white_opening();
  else if (nb_move_ < 4)
    move = make_black_opening();
  else
    move = std::get<1>(minimax(color_, 4));
  nb_move_++;
  return move;
}

std::pair<int, Move> AwesomeAi::minimax(Color color, int step)
{
  if (step == 0)
    //fonction d'evaluation
    return std::pair<int, Move>(/*fct eval*/5, Move());

  int value;
  if (color == color_)
    value = INT_MIN;
  else
    value = INT_MAX;

 //We get all pieces then all the possible moves
  Vector<Position> pieces_pos = board_.get_pieces(color);
  Vector<Move> moves;
  for (Position p_pos : pieces_pos)
    {
      Vector<Move> tmp = chessboard.get_possible_moves(p_pos);
      moves.insert(moves.end(), tmp.begin(), tmp.end());
    }

  std::pair<int, Move> result(value, Move());
  bool is_max_turn;
  if (color == color_)
    is_max_turn = true;
  else
    is_max_turn = false;

  //let's start minimax
  for (Move cur_move : moves)
    {
      Color next_color;
      if (color == Color::WHITE)
        next_color = Color::BLACK;
      else
        next_color = Color::WHITE;
      std::pair<int, Move> tmp_res = minimax(next_color, step - 1);
      if (is_max_turn)
        {
          if (std::get<0>(tmp_res) > std::get<0>(result))
            result = std::pair<int, Move>(std::get<0>(tmp_res), std::get<1>(result));
        }
      else
        {
          if (std::get<0>(tmp_res) < std::get<0>(result))
            result = std::pair<int, Move>(std::get<0>(tmp_res), std::get<1>(result));
        }
    }

  //sinon
  //On get toute les piece de couleur color
  //on get tous les mov de toutes les pieces
  //minimax dessus avec (color inverse, step -1)
  /* TODO : RECURSIVE METHODES !!!! */
}

Move AwesomeAi::make_white_opening()
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

Move AwesomeAi::make_black_opening()
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

const std::string& AwesomeAi::name_get()
{
  return name_;
}
