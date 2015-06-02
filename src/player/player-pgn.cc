#include "player-pgn.hh"

PlayerPGN::PlayerPGN(Color color, std::vector<std::string> moves)
  : PlayerAbstract(color)
  , moves_(moves)
{
  iterator = moves_.begin();
}

PlayerPGN::~PlayerPGN()
{}

Move PlayerPGN::move_get()
{
  eat = false;
  std::string raw_move = *iterator;
  iterator++;
  std::cout << "raw_move == " << raw_move << std::endl;

  //Check if this is a rock
  if (raw_move[0] == 'O')
  {
    if (raw_move == "O-O")
    {
      return little_rock();
    }
    else
    {
      return big_rock();
    }
  }

  int index = 0;
  std::string first_prev_emplacement;
  std::string second_prev_emplacement;
  //Check if there is a indication on the previous emplacement of the piece
  if (is_emplacement(raw_move.substr(index, 1)))
    first_prev_emplacement = raw_move[index++];
  if (is_emplacement(raw_move.substr(index, 1)))
    second_prev_emplacement = raw_move[index++];

  PieceType type = get_piece_type(raw_move, index++);
  std::cout << "PieceType == " << type << std::endl;

  if (type == PieceType::NONE)
    return Move();

  if (raw_move.substr(index, 1) == "x")
    {
      index++;
      eat = true;
    }

  Position end(fileMap_[raw_move.substr(index, 1)],
               rankMap_[raw_move.substr(index + 1, 1)]);
  if (end.file_get() == Position::FILE_FIRST ||
      end.rank_get() == Position::RANK_FIRST)
    return Move();

  Position::File f_start = fileMap_[first_prev_emplacement];
  Position::Rank r_start = rankMap_[second_prev_emplacement];

  Position begin;
  if (f_start != Position::FILE_FIRST && r_start != Position::RANK_FIRST)
    begin = Position(f_start, r_start);
  else
    begin = get_old_position(type, end, f_start, r_start);
  /**
  * Parse the raw move to get the position and the piece type
  * check all the possibility where the piece could come from
  * if there is one piece, this is the right one
  * else, return move()
  **/



  return Move(begin, end, PieceType::NONE);
}

Position PlayerPGN::get_old_position(PieceType type,
                                     Position new_pos,
                                     Position::File f_start,
                                     Position::Rank r_start)
{
//  first_prev_emplacement = second_prev_emplacement;
//  type = type;
//  new_pos = new_pos;

  switch(type)
    {
    case PieceType::PAWN:
      return find_old_pawn(new_pos, f_start, r_start);
      break;
    case PieceType::BISHOP:
      return find_old_bishop(new_pos, f_start, r_start);
      break;
    case PieceType::KING:
      return find_old_king(new_pos, f_start, r_start);
      break;
    case PieceType::QUEEN:
      return find_old_queen(new_pos, f_start, r_start);
      break;
    case PieceType::KNIGHT:
      return find_old_knight(new_pos, f_start, r_start);
      break;
    case PieceType::ROOK:
      return find_old_rook(new_pos, f_start, r_start);
      break;
    default:
      break;
    }
  //if (type == PieceType::PAWN)
  return Position();
}

Position PlayerPGN::find_old_pawn(Position new_pos,
                                  Position::File f, Position::Rank r)
{
/*  Piece p;
  Position::File file = fileMap_[std::get<0>new_pos];
  Position::Rank rank = rankMap_[std::get<1>new_pos];
  if (color_ == Color::WHITE)
    {
      for (int i = 0; i < 2; i++)
        {
          p = board_.get_piece_pos(file, --rank);
          if (p.get_type == PieceType::PAWN && p.get_color == Color::WHITE)
            return Position(file, rank);
        }
    }
  else
    {
      for (int i = 0; i < 2; i++)
        {
          p = board.get_piece_pos(file, ++rank);
          if (p.get_type == PieceType::PAWN && p.get_color == Color::BLACK)
            return Position(file, rank);
        }
    }
  return Position();*/

  new_pos = new_pos;
  f = f;
  r = r;
  return Position();
}

Position PlayerPGN::find_old_bishop(Position new_pos,
                                    Position::File f, Position::Rank r)
{
  new_pos = new_pos;
  f = f;
  r = r;
  return Position();
}

Position PlayerPGN::find_old_king(Position new_pos,
                                  Position::File f, Position::Rank r)
{
  new_pos = new_pos;
  f = f;
  r = r;
  return Position();
}

Position PlayerPGN::find_old_queen(Position new_pos,
                                   Position::File f, Position::Rank r)
{
  new_pos = new_pos;
  f = f;
  r = r;
  return Position();
}

Position PlayerPGN::find_old_knight(Position new_pos,
                                    Position::File f, Position::Rank r)
{
  new_pos = new_pos;
  f = f;
  r = r;
  return Position();
}


Position PlayerPGN::find_old_rook(Position new_pos,
                                  Position::File f, Position::Rank r)
{
  Position::File f_tmp = f;
  Position::Rank r_tmp = r;
  // if file or rank is null, we increment it at least to the first enum
  if (f == Position::FILE_FIRST)
    ++f_tmp;
  if (r == Position::RANK_FIRST)
    ++r_tmp;

  while (f_tmp != Position::FILE_LAST && r_tmp != Position::RANK_LAST)
  {
    Piece piece = board_.get_piece_pos(Position(f_tmp, r_tmp));
    Move m_tmp(Position(f_tmp, r_tmp), new_pos);
    if (piece.get_type() == ROOK &&
        board_.check_move(m_tmp, last_opponent_move_.end_get()))
      return Position(f_tmp, r_tmp);

    // INCREMENTATION PART
    if (f == Position::FILE_FIRST)
      ++f_tmp;
    else
      ++r_tmp;
    // If we are at the end of the line
    if (f_tmp == Position::FILE_LAST)
    {
      // If rank is unknown : double loop
      if (r == Position::RANK_FIRST)
      {
        f_tmp = Position::ANNA;
        ++r_tmp;
      }
      else
      {
        //end of loop on file
        break;
      }
    }
  }
  return Position();
}

PieceType PlayerPGN::get_piece_type(std::string raw_move, int index)
{
  //No piece specifide
  if (fileMap_[raw_move.substr(index, 1)] != Position::FILE_FIRST)
    return PieceType::PAWN;
  PieceType res = pieceMap_[raw_move.substr(index, 1)];
  if (res == PieceType::KING && raw_move.substr(index, 1) != "K")
    return PieceType::NONE;
  return res;
}

void PlayerPGN::setMoves(std::vector<std::string> moves)
{
  this->moves_ = moves;
}

void PlayerPGN::last_opponent_move_set(const Move& last_opponent_move)
{
  last_opponent_move_ = last_opponent_move;
  board_.make_move(last_opponent_move);
}

Move PlayerPGN::little_rock()
{
  std::cout << "LITTLE ROCK METHOD" << std::endl;
  if (color_ == Color::WHITE)
  {
    Position begin(Position::EVA, Position::EINS);
    Position end(Position::GUSTAV, Position::EINS);
    return Move(begin, end, PieceType::NONE);
  }
  else
  {
    Position begin(Position::EVA, Position::ACHT);
    Position end(Position::GUSTAV, Position::ACHT);
    return Move(begin, end, PieceType::NONE);
  }
}

Move PlayerPGN::big_rock()
{
  std::cout << "BIG ROCK METHOD" << std::endl;
  if (color_ == Color::WHITE)
  {
    Position begin(Position::EVA, Position::EINS);
    Position end(Position::CESAR, Position::EINS);
    return Move(begin, end);
  }
  else
  {
    Position begin(Position::EVA, Position::ACHT);
    Position end(Position::CESAR, Position::ACHT);
    return Move(begin, end);
  }
}

bool PlayerPGN::is_emplacement(std::string c)
{
  if (rankMap_[c] != Position::RANK_FIRST ||
      fileMap_[c] != Position::FILE_FIRST)
    return true;
  return false;
}

void PlayerPGN::print()
{
  std::cout << "=======================" << std::endl;
  std::cout << "==== player  print ====" << std::endl;
  if (this->color_ == Color::WHITE)
    std::cout << "White player" << std::endl;
  else if (this->color_ == Color::BLACK)
    std::cout << "Black player" << std::endl;

  int i(1);
  for (std::string st : this->moves_)
  {
    std::cout << "Move " << i << " : " << st << std::endl;
    ++i;
  }
  std::cout << "=======================" << std::endl;
}
