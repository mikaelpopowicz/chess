#include "player-pgn.hh"

PlayerPGN::PlayerPGN(Color color, std::vector<std::string> moves)
  : PlayerAbstract(color)
  , moves_(moves)
{
  iterator = moves_.begin();
  last_opponent_move_ = Move(Position(Position::FILE_FIRST,
                                      Position::RANK_FIRST),
                            (Position(Position::FILE_FIRST,
                                      Position::RANK_FIRST)));
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

  Position pos_nul(Position::FILE_FIRST, Position::RANK_FIRST);

  int index = 0;
  std::string first_prev_emplacement;
  std::string second_prev_emplacement;
  PieceType type = get_piece_type(raw_move, index);

  if (type == PieceType::NONE)
    return Move(pos_nul, pos_nul);

  if (rankMap_[raw_move.substr(raw_move.size() - 1)] == Position::RANK_FIRST)
  {
    if (raw_move[raw_move.size() - 1] != '+' &&
        raw_move[raw_move.size() - 1] != '#')
      return Move(pos_nul, pos_nul);
    else
      raw_move = raw_move.substr(0, raw_move.size() - 1);
  }

   //Check if there is a indication on the previous emplacement of the piece
  if (raw_move.size() - index > 2 && is_emplacement(raw_move.substr(index, 1)))
    first_prev_emplacement = raw_move[index++];
  if (raw_move.size() - index > 2 && is_emplacement(raw_move.substr(index, 1)))
    second_prev_emplacement = raw_move[index++];

  if (raw_move.substr(index, 1) == "x")
    {
      index++;
      eat = true;
    }

  std::cout << "PieceType == " << type << std::endl;
  std::cout << "last opponent move:" << last_opponent_move_ << std::endl;;

  Position end(fileMap_[raw_move.substr(index, 1)],
               rankMap_[raw_move.substr(index + 1, 1)]);
  if (end.file_get() == Position::FILE_FIRST)
    return Move(pos_nul, pos_nul);

  Position::File f_start = fileMap_[first_prev_emplacement];
  Position::Rank r_start = rankMap_[second_prev_emplacement];

  Position begin;
  if (f_start != Position::FILE_FIRST && r_start != Position::RANK_FIRST)
    begin = Position(f_start, r_start);
  else
    begin = get_old_position(type, end, f_start, r_start);

  Move m(begin, end);
  board_.make_move(m);
  return m;
}

Position PlayerPGN::get_old_position(PieceType type,
                                     Position new_pos,
                                     Position::File f_start,
                                     Position::Rank r_start)
{
  Position::File f_tmp = f_start;
  Position::Rank r_tmp = r_start;
  // if file or rank is null, we increment it at least to the first enum
  if (f_start == Position::FILE_FIRST)
    ++f_tmp;
  if (r_start == Position::RANK_FIRST)
    ++r_tmp;

  while (f_tmp != Position::FILE_LAST && r_tmp != Position::RANK_LAST)
  {
    Piece piece = board_.get_piece_pos(Position(f_tmp, r_tmp));
    Move m_tmp(Position(f_tmp, r_tmp), new_pos);

    // We check if the piece has the good type & move is possible
    if (piece.get_type() == type && piece.get_color() == color_ &&
        board_.check_move(m_tmp, last_opponent_move_.end_get()))
      return Position(f_tmp, r_tmp);

    // INCREMENTATION PART
    if (f_start == Position::FILE_FIRST)
      ++f_tmp;
    else
      ++r_tmp;
    // If we are at the end of the line
    if (f_tmp == Position::FILE_LAST)
    {
      // If rank is unknown : double loop
      if (r_start == Position::RANK_FIRST)
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
  return Position(Position::FILE_FIRST, Position::RANK_FIRST);
}

PieceType PlayerPGN::get_piece_type(std::string raw_move, int& index)
{
  //No piece specifide
  if (fileMap_[raw_move.substr(index, 1)] != Position::FILE_FIRST &&
      fileMap_[raw_move.substr(index, 1)] != Position::FILE_LAST)
    return PieceType::PAWN;
  PieceType res = pieceMap_[raw_move.substr(index, 1)];
  if (res == PieceType::KING && raw_move.substr(index, 1) != "K")
    return PieceType::NONE;
  ++index;
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
