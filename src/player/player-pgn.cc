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

  if (fileMap_[raw_move.substr(index, 1)] == Position::FILE_FIRST
    || rankMap_[raw_move.substr(index + 1, 1)] == Position::RANK_FIRST)
    return Move();

  std::pair<std::string, std::string> new_position(raw_move.substr(index, 1),
                                                 raw_move.substr(index + 1, 1));

  Position begin = get_old_position(type, new_position,
                               first_prev_emplacement, second_prev_emplacement);
  Position end(fileMap_[std::get<0>(new_position)],
               rankMap_[std::get<1>(new_position)]);
  /**
  * Parse the raw move to get the position and the piece type
  * check all the possibility where the piece could come from
  * if there is one piece, this is the right one
  * else, return move()
  **/



  return Move(begin, end, PieceType::NONE);
}

Position PlayerPGN::get_old_position(PieceType type,
                                     std::pair<std::string, std::string> new_pos,
                                     std::string first_prev_emplacement,
                                     std::string second_prev_emplacement)
{
  first_prev_emplacement = second_prev_emplacement;
  type = type;
  new_pos = new_pos;

  switch(type)
    {
    case PieceType::PAWN:
      return find_old_pawn(new_pos, first_prev_emplacement,
                           second_prev_emplacement);
      break;
    case PieceType::BISHOP:
      return find_old_bishop(new_pos, first_prev_emplacement,
                             second_prev_emplacement);
      break;
    case PieceType::KING:
      return find_old_king(new_pos, first_prev_emplacement,
                           second_prev_emplacement);
      break;
    case PieceType::QUEEN:
      return find_old_queen(new_pos, first_prev_emplacement,
                            second_prev_emplacement);
      break;
    case PieceType::KNIGHT:
      return find_old_knight(new_pos, first_prev_emplacement,
                             second_prev_emplacement);
      break;
    case PieceType::ROOK:
      return find_old_rook(new_pos, first_prev_emplacement,
                           second_prev_emplacement);
      break;
    default:
      break;
    }
  //if (type == PieceType::PAWN)
  return Position();
}

Position PlayerPGN::find_old_pawn(std::pair<std::string, std::string> new_pos,
                                  std::string f_prev, std::string s_prev)
{
  Piece p;
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
  return Position();
}

Position PlayerPGN::find_old_bishop(std::pair<std::string, std::string> new_pos,
                                    std::string f_prev, std::string s_prev)
{
  new_pos = new_pos;
  f_prev = s_prev;
  return Position();
}

Position PlayerPGN::find_old_king(std::pair<std::string, std::string> new_pos,
                                  std::string f_prev, std::string s_prev)
{
  new_pos = new_pos;
  f_prev = s_prev;
  return Position();
}
1
Position PlayerPGN::find_old_queen(std::pair<std::string, std::string> new_pos,
                                   std::string f_prev, std::string s_prev)
{
  new_pos = new_pos;
  f_prev = s_prev;
  return Position();
}

Position PlayerPGN::find_old_knight(std::pair<std::string, std::string> new_pos,
                                    std::string f_prev, std::string s_prev)
{
  new_pos = new_pos;
  f_prev = s_prev;
  return Position();
}

Position PlayerPGN::find_old_rook(std::pair<std::string, std::string> new_pos,
                                  std::string f_prev, std::string s_prev)
{
  new_pos = new_pos;
  f_prev = s_prev;
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
