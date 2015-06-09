#include "chessboard.hh"
#include "position.hh"
#include "color.hh"
#include "piece-type.hh"

#include <vector>
#include <cmath>
#include <algorithm>

Chessboard::Chessboard()
  : white_king_moved_(false),
    black_king_moved_(false),
    white_king_(Position(Position::EVA, Position::EINS)),
    black_king_(Position(Position::EVA, Position::ACHT)),
    previous_moved_(Position(Position::FILE_FIRST, Position::RANK_FIRST))
{
  for (int row = 0; row < SIZE; ++row)
    for (int col = 0; col < SIZE; ++col)
    {
      Color c = BLACK;
      PieceType pt = NONE;
      if (row <= 1)
        c = WHITE;
      if (row == 0 || row == SIZE - 1)
      {
        if (col == 0 || col == 7)
          pt = ROOK;
        else if (col == 1 || col == 6)
          pt = KNIGHT;
        else if (col == 2 || col == 5)
          pt = BISHOP;
        else if (col == 3)
          pt = QUEEN;
        else
          pt = KING;
      }
      else if (row == 1 || row == SIZE - 2)
        pt = PAWN;

      board_[row][col].set_type(pt);
      board_[row][col].set_color(c);
    }

  // Add the initial positions of the rook
  initial_rooks_.push_back(Position(Position::ANNA, Position::EINS));
  initial_rooks_.push_back(Position(Position::HECTOR, Position::EINS));
  initial_rooks_.push_back(Position(Position::ANNA, Position::ACHT));
  initial_rooks_.push_back(Position(Position::HECTOR, Position::ACHT));
}

Chessboard::~Chessboard()
{
}

Piece Chessboard::get_piece_pos(const Position& p) const
{
  return get_piece(p.file_get(), p.rank_get());
}

Piece& Chessboard::get_piece_pos(const Position& p)
{
  return get_piece(p.file_get(), p.rank_get());
}

Piece Chessboard::get_piece(Position::File f, Position::Rank r) const
{
  return board_[r - 1][f - 1];
}

Piece& Chessboard::get_piece(Position::File f, Position::Rank r)
{
  return board_[r - 1][f - 1];
}

int Chessboard::make_move(Move m)
{
  Piece p = get_piece_pos(m.start_get());
  int line_start = m.start_get().rank_get() - 1;
  int col_start = m.start_get().file_get() - 1;
  int line_end = m.end_get().rank_get() - 1;
  int col_end = m.end_get().file_get() - 1;
  Piece p_end = get_piece_pos(m.end_get());

  if (p.get_type() == NONE || line_start == -1 || col_start == -1 ||
      line_end == -1 || col_end == -1)
    return -1;

  int res = 0;
  //Move the piece
  board_[line_start][col_start] = Piece(NONE, BLACK);
  board_[line_end][col_end] = p;


  // If the king is moved
  if (p.get_type() == KING)
  {
    bool king_moved = (p.get_color() == WHITE && white_king_moved_)
          || (p.get_color() == BLACK && black_king_moved_);

    // in case of a castling kingside
    if (!king_moved && m.end_get().file_get() == Position::GUSTAV)
    {
      auto pos = std::find(initial_rooks_.begin(), initial_rooks_.end(),
                           Position(Position::HECTOR,
                                    get_king_pos(p.get_color()).rank_get()));
      if (pos != initial_rooks_.end())
      {
        // moving the rook
        board_[line_end][col_end - 1] = board_[line_end][7];
        board_[line_end][7] = Piece(NONE, BLACK);
        res = 2;
        initial_rooks_.erase(pos);
      }
      else
        return -1;
    }

    // in case of a castling queenside
    else if (!king_moved && m.end_get().file_get() == Position::CESAR)
    {
      auto pos = std::find(initial_rooks_.begin(), initial_rooks_.end(),
                           Position(Position::ANNA,
                                    get_king_pos(p.get_color()).rank_get()));
      if (pos != initial_rooks_.end())
      {
        //moving the rook
        board_[line_end][col_end + 1] = board_[line_end][0];
        board_[line_end][0] = Piece(NONE, BLACK);
        res = 3;
        initial_rooks_.erase(pos);
      }
      else
        return -1;
    }

    if (p.get_color() == WHITE)
    {
      white_king_moved_ = true;
      white_king_ = m.end_get();
    }
    else
    {
      black_king_moved_ = true;
      black_king_ = m.end_get();
    }
  }

  else if (p.get_type() == PAWN)
  {
    // If there is a promotion
    if (m.promotion_get() != NONE && p.get_type() == PAWN)
    {
      res = 1;
      board_[line_end][col_end].set_type(m.promotion_get());
    }
    Position pos(m.end_get().file_get(), m.start_get().rank_get());
    Piece& tmp = get_piece(pos.file_get(), pos.rank_get());

    bool en_passant = previous_moved_ == pos &&
      tmp.get_type() == PAWN &&
      ((tmp.get_color() == WHITE && pos.rank_get() == Position::VIER) ||
       (tmp.get_color() == BLACK && pos.rank_get() == Position::FUNF));
    if (en_passant)
      tmp.set_type(NONE);
  }

  else if (p.get_type() == ROOK)
  {
    auto pos = std::find(initial_rooks_.begin(), initial_rooks_.end(),
                         m.start_get());
    if (pos != initial_rooks_.end())
      initial_rooks_.erase(pos);
  }

  history_.push_back(std::make_pair(m, p_end));
  previous_moved_ = m.end_get();
  return res;
}

bool Chessboard::undo()
{
  if (history_.size() == 0)
    return false;

  auto todelete = history_.back();
  Move m_todelete = todelete.first;
  Position m_start = m_todelete.start_get();
  Piece piece_tomove = get_piece_pos(m_todelete.end_get());
  get_piece_pos(m_start).set_type(piece_tomove.get_type());
  get_piece_pos(m_start).set_color(piece_tomove.get_color());

  if (m_todelete.promotion_get() != NONE)
    get_piece(m_start.file_get(), m_start.rank_get()).set_type(PAWN);

  history_.erase(history_.end() - 1);

  get_piece_pos(m_todelete.end_get()).set_type(todelete.second.get_type());
  get_piece_pos(m_todelete.end_get()).set_color(todelete.second.get_color());
  previous_moved_ = history_.back().first.end_get();
  return true;
}

bool Chessboard::has_king_moved(Color c)
{
  if (c == WHITE)
    return white_king_moved_;
  else
    return black_king_moved_;
}

Position Chessboard::get_king_pos(Color c)
{
  if (c == WHITE)
    return white_king_;
  else
    return black_king_;
}

bool Chessboard::is_player_check(Position pos_king)
{
  Position::File f = Position::ANNA;
  Position::Rank r = Position::EINS;
  Piece king = get_piece_pos(pos_king);
  while (r != Position::RANK_LAST)
  {
    Position pos_now(f, r);
    Piece tmp = get_piece(f, r);
    if (tmp.get_type() != NONE && tmp.get_color() != king.get_color() &&
        check_move(Move(pos_now, pos_king)))
      return true;

    ++f;
    if (f == Position::FILE_LAST)
    {
      f = Position::ANNA;
      ++r;
    }
  }
  return false;
}

bool Chessboard::is_player_mat(Position pos_king)
{
  if (!is_player_check(pos_king))
    return false;
  Piece king = get_piece_pos(pos_king);

  std::vector<Position> pieces_pos;
  Position::File f = Position::ANNA;
  Position::Rank r = Position::EINS;
  while (r != Position::RANK_LAST)
  {
    Piece p = get_piece(f, r);
    if (p.get_type() != NONE &&
        p.get_color() == king.get_color())
      pieces_pos.push_back(Position(f, r));
    ++f;
    if (f == Position::FILE_LAST)
    {
      f = Position::ANNA;
      ++r;
    }
  }

  for (unsigned int i = 0; i < pieces_pos.size(); ++i)
  {
    f = Position::ANNA;
    r = Position::EINS;
    while (r != Position::RANK_LAST)
    {

      Position pos_tmp(f, r);
      Move m(pieces_pos[i], pos_tmp);

      if (check_move(m))
      {
        make_move(m);
        bool is_check = is_player_check(get_king_pos(king.get_color()));
        if (!is_check)
        {
          undo();
          return false;
        }
        undo();
      }

      ++f;
      if (f == Position::FILE_LAST)
      {
        f = Position::ANNA;
        ++r;
      }
    }
  }
  return true;
}

bool Chessboard::is_player_pat(Color c)
{
  std::vector<Position> pos_pieces;
  std::vector<Position> others;

  //First loop to find which pieces belongs to the player
  Position::File f = Position::ANNA;
  Position::Rank r = Position::EINS;
  while (r != Position::RANK_LAST)
  {
    Piece p_tmp = get_piece(f, r);
    if (p_tmp.get_type() != NONE && p_tmp.get_color() ==c)
      pos_pieces.push_back(Position(f, r));
    else
      others.push_back(Position(f, r));
    ++f;
    if (f == Position::FILE_LAST)
    {
      f = Position::ANNA;
      ++r;
    }
  }
  // For each piece, it checks if it can go to the others positions
  for (Position p_piece : pos_pieces)
    for (Position p_other : others)
      if (check_move(Move(p_piece, p_other)))
        return false;
  return true;
}

bool Chessboard::is_threefold_repetition(std::vector<Chessboard> history)
{
  int repetition = 0;
  for (Chessboard cb : history)
  {
    if (cb == *this)
      ++repetition;
    if (repetition >= 3)
      return true;
  }
  return false;
}

bool Chessboard::check_move(Move m)
{
  Piece p = get_piece_pos(m.start_get());
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();
  Piece p_tmp = get_piece(f_end, r_end);

  if (p_tmp.get_type() != NONE && p_tmp.get_color() == p.get_color())
    return false;

  if (p.get_type() == PAWN)
    return check_pawn_move(m, p);

  else if (p.get_type() == KNIGHT)
    return check_knight_move(m);

  else if (p.get_type() == BISHOP)
    return check_bishop_move(m);

  else if (p.get_type() == ROOK)
    return check_rook_move(m);

  else if (p.get_type() == QUEEN)
    return check_rook_move(m) || check_bishop_move(m);

  else if (p.get_type() == KING)
    return check_king_move(m, p.get_color());

  return false;
}

bool Chessboard::check_pawn_move(Move m, Piece p)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();
  Position::Rank r_tmp = r_start;
  bool same_col = f_start == f_end;
  bool is_whi = p.get_color() == WHITE;
  bool white_init = r_start == Position::ZWEI;
  bool black_init = r_start == Position::SIEBEN;
  Piece p_end = get_piece(f_end, r_end);
  // If same column & one cell moved or 2 at the beginning :
  if (same_col && p_end.get_type() == NONE &&
      ((is_whi && (r_end == ++r_tmp || (white_init && r_end == ++r_tmp)))
       || (!is_whi && (r_end == --r_tmp || (black_init && r_end == --r_tmp)))
      ))
    return true;
  // else if "en passant"
  else if (!same_col)
  {
    r_tmp = r_start;
    Position pos(f_end, r_start);
    Piece& tmp = get_piece(pos.file_get(), pos.rank_get());

    bool en_passant = tmp.get_type() == PAWN && previous_moved_ == pos
      && tmp.get_color() != p.get_color()
      && ((tmp.get_color() == WHITE && pos.rank_get() == Position::VIER)
          || (tmp.get_color() == BLACK && pos.rank_get() == Position::FUNF));

    //If the pawn goes on an adjacent column
    if ((is_whi && r_end == ++r_tmp && fabs(f_start - f_end) == 1)
        || (!is_whi && r_end == --r_tmp && fabs(f_start - f_end) == 1))
    {
      // If the goal of the pawn is an opponent piece
      if ((p_end.get_color() != p.get_color() && p_end.get_type() != NONE))
        return true;
      // Else if the previous move was a pawn which moved 2 cells
      else if (en_passant)
        return true;
    }
  }
  return false;
}

bool Chessboard::check_rook_move(Move m)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();

  // if same line
  if (r_start == r_end)
  {
    Position::File f_tmp = f_start;
    if (f_end > f_start)
      ++f_tmp;
    else
      --f_tmp;
    while (f_tmp != f_end)
    {
      Piece p_tmp = get_piece(f_tmp, r_start);
      if (p_tmp.get_type() != NONE)
        return false;

      if (f_end > f_start)
        ++f_tmp;
      else
        --f_tmp;
    }
  }
  // if same column
  else if (f_start == f_end)
  {
    Position::Rank r_tmp = r_start;
    if (r_end > r_start)
      ++r_tmp;
    else
      --r_tmp;
    while (r_tmp != r_end)
    {
      Piece p_tmp = get_piece(f_start, r_tmp);
      if (p_tmp.get_type() != NONE)
        return false;
      if (r_end > r_start)
        ++r_tmp;
      else
        --r_tmp;
    }
  }
  else if (r_start != r_end && f_start != f_end)
    return false;
  return true;
}

bool Chessboard::check_knight_move(Move m)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();

  if ((fabs(f_start - f_end) == 2 && fabs(r_start - r_end) == 1)
      ||(fabs(f_start - f_end) == 1 && fabs(r_start - r_end) == 2))
    return true;

  return false;
}

bool Chessboard::check_bishop_move(Move m)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();
  // If in diagonal
  if (fabs(f_start - f_end) == fabs(r_start - r_end))
  {
    // Check if there is no piece
    Position::File f_tmp = f_start;
    Position::Rank r_tmp = r_start;
    if (f_end > f_start)
      ++f_tmp;
    else
      --f_tmp;
    if (r_end > r_start)
      ++r_tmp;
    else
      --r_tmp;
    while (f_tmp != f_end)
    {
      Piece p_tmp = get_piece(f_tmp, r_tmp);
      if (p_tmp.get_type() != NONE)
        return false;
      if (f_end > f_start)
        ++f_tmp;
      else
        --f_tmp;
      if (r_end > r_start)
        ++r_tmp;
      else
        --r_tmp;
    }
    return true;
  }
  return false;
}

bool Chessboard::check_king_move(Move m, Color c)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();

  // If it's an 'ordinary' move (one cell distance)
  if (fabs(f_end - f_start) <= 1 && fabs(r_end - r_start) <= 1)
  {
    Position::File f = Position::ANNA;
    Position::Rank r = Position::EINS;
    while (r != Position::RANK_LAST)
    {
      Piece tmp = get_piece(f, r);
      if (tmp.get_type() != NONE && tmp.get_type() != KING
          && tmp.get_color() != c
          && check_move(Move(Position(f, r), Position(f_end, r_end))))
        return false;
      ++f;
      if (f == Position::FILE_LAST)
      {
        f = Position::ANNA;
        ++r;
      }
    }
    return true;
  }

  // If one of the distance (file or rank) is longer than 2
  else if (fabs(f_end - f_start) + fabs(r_end - r_start) > 2)
    return false;

  // else if the king has never moved
  else if (!has_king_moved(c))
  {
    //Finding the file of the concerned rook
    Position::File f_rook = Position::ANNA;
    if (m.end_get().file_get() == Position::GUSTAV)
      f_rook = Position::HECTOR;
    // If the rook concerned has moved, castling is impossible
    bool rook_moved = std::find(initial_rooks_.begin(),
                                initial_rooks_.end(),
                                Position(f_rook, get_king_pos(c).rank_get()))
                      == initial_rooks_.end();
    if (rook_moved)
      return false;
    Position::File f_tmp = f_start;
    if (f_end > f_start)
      ++f_tmp;
    else
      --f_tmp;
    while (f_tmp != f_end)
    {
      Piece p_tmp = get_piece(f_tmp, r_start);
      // If we find a piece on the way:
      if (p_tmp.get_type() != NONE)
        return false;
      Position::File f = Position::ANNA;
      Position::Rank r = Position::EINS;
      // If this position is threatened
      while (r != Position::RANK_LAST)
      {
        Piece tmp = get_piece(f, r);
        if (tmp.get_type() != NONE && tmp.get_type() != KING
            && tmp.get_color() != c
            && check_move(Move(Position(f, r), Position(f_tmp, r_start))))
          return false;
        ++f;
        if (f == Position::FILE_LAST)
        {
          f = Position::ANNA;
          ++r;
        }
      }
      if (f_end > f_start)
        ++f_tmp;
      else
        --f_tmp;
    }
    return true;
  }
  return false;
}

void Chessboard::print()
{
  std::string red = "\033[1;31m";
  std::string green = "\033[1;32m";
  std::string normal = "\033[0m";
  for (int row = 7; row >= 0; --row)
  {
    std::cout << " " << row + 1 << " ";
    for (int col = 0; col < 8; ++col)
    {
      Piece p = board_[row][col];
      if (p.get_color() == 0)
        std::cout << "[" << green;
      else
        std::cout << "[" << red;
      if (p.get_type() == NONE)
        std::cout << " ";
      else if (p.get_type() == KING)
        std::cout << "K";
      else if (p.get_type() == QUEEN)
        std::cout << "Q";
      else if (p.get_type() == KNIGHT)
        std::cout << "N";
      else if (p.get_type() == ROOK)
        std::cout << "R";
      else if (p.get_type() == BISHOP)
        std::cout << "B";
      else
        std::cout << "P";
      std::cout << normal << "]";
    }
  std::cout << std::endl;
  }
  std::cout << "    a  b  c  d  e  f  g  h"
            << std::endl;
  std::cout << std::endl;
}

std::vector<Position> Chessboard::get_pieces(Color color)
{
  std::vector<Position> pos_pieces;
  Position::File f = Position::ANNA;
  Position::Rank r = Position::EINS;

  while (r != Position::RANK_LAST)
  {
    Piece p_tmp = get_piece(f, r);
    if (p_tmp.get_type() != NONE && p_tmp.get_color() == color)
      pos_pieces.push_back(Position(f, r));
    ++f;
    if (f == Position::FILE_LAST)
    {
      f = Position::ANNA;
      ++r;
    }
  }
  return pos_pieces;
}

std::vector<Position> Chessboard::get_possible_moves(Position pos_piece)
{
  std::vector<Position> pos;
  Piece p = get_piece_pos(pos_piece);
  if (p.get_type() == PAWN)
    pos = get_moves_pawn(pos_piece);
  return pos;
}

std::vector<Position> Chessboard::get_moves_pawn(Position pos_piece)
{
  std::vector<Position> pos;
  Piece p = get_piece_pos(pos_piece);
  Position::Rank r = pos_piece.rank_get();
  Position::File f = pos_piece.file_get();

  if (p.get_color() == WHITE)
  {
    // If cell next to the pawn
    if (board_[f - 1][r].get_type() == NONE)
    {
      pos.push_back(Position(f, static_cast<Position::Rank>(r + 1)));
      // If cell 2 ranks ahead
      if (r == Position::ZWEI && board_[f - 1][r + 1].get_type() == NONE)
        pos.push_back(Position(f, static_cast<Position::Rank>(r + 2)));
    }
    // If catching piece on the left or en_passant left
    if (f != Position::ANNA &&
        ((board_[f - 2][r].get_type() != NONE &&
          board_[f - 2][r].get_color() != p.get_color()) ||
         (previous_moved_ == Position(static_cast<Position::File>(f-1), r) &&
          board_[f - 2][r].get_type() == NONE) ))
    {
      pos.push_back(Position(static_cast<Position::File>(f - 1),
                             static_cast<Position::Rank>(r + 1)));
    }
    // If catching piece on the right or en_passant right
    if (f != Position::HECTOR &&
        ((board_[f][r].get_type() != NONE &&
          board_[f][r].get_color() != p.get_color()) ||
         (previous_moved_ == Position(static_cast<Position::File>(f+1), r) &&
          board_[f][r].get_type() == NONE) ))
      pos.push_back(Position(static_cast<Position::File>(f + 1),
                             static_cast<Position::Rank>(r + 1)));
  }
  else if (p.get_color() == BLACK)
  {
    if (board_[f - 1][r - 2].get_type() == NONE)
    {
      pos.push_back(Position(f, static_cast<Position::Rank>(r - 1)));
      if (r == Position::SIEBEN && board_[f - 1][r - 3].get_type() == NONE)
        pos.push_back(Position(f, static_cast<Position::Rank>(r - 2)));
    }
    if (f != Position::ANNA &&
        ((board_[f - 2][r - 2].get_type() != NONE &&
          board_[f - 2][r - 2].get_color() != p.get_color()) ||
         (previous_moved_ == Position(static_cast<Position::File>(f-1), r) &&
          board_[f - 2][r - 1].get_type() == NONE) ))
    {
      pos.push_back(Position(static_cast<Position::File>(f - 1),
                             static_cast<Position::Rank>(r - 1)));
    }
    if (f != Position::HECTOR &&
        ((board_[f][r - 2].get_type() != NONE &&
          board_[f][r - 2].get_color() != p.get_color()) ||
         (previous_moved_ == Position(static_cast<Position::File>(f+1), r) &&
          board_[f][r - 2].get_type() == NONE) ))
      pos.push_back(Position(static_cast<Position::File>(f + 1),
                             static_cast<Position::Rank>(r - 1)));
  }
  return pos;
}
