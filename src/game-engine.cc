#include "game-engine.hh"
#include <cmath>

  GameEngine::GameEngine(Player* p1, Player* p2)
: p1_(p1),
  p2_(p2),
  nb_turn_no_move_(0)
{
  history_.push_back(actual_);
}

GameEngine::~GameEngine()
{
}

/*void GameEngine::set_observer(Observer o)
  {
  }*/

int GameEngine::play()
{
  //Begin the game
  //Color color_turn = WHITE;
  while (is_finished() == 0)
  {
  }

  // While game not finished:

  //Get a move from the Player 1
  //Check move & rules ok
  //Make move
  //Get a move from the Player 2
  //Check move & rules ok
  //Make move
  return 0;
}

bool GameEngine::check_pawn_move(Move m, Piece p)
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
  // If same column & one cell moved or 2 at the beginning :
  if (same_col &&
      ((is_whi && (r_end == ++r_tmp || (white_init && r_end == ++r_tmp)))
       || (!is_whi && (r_end == --r_tmp || (black_init && r_end == --r_tmp)))
      ))
    return true;
  // else if "en passant"
  else if (!same_col)
  {
    Piece p_end = actual_.get_piece(f_end, r_end);
    //TODO make bool en passant
    bool en_passant = false;
    if ((is_whi && r_end == ++r_tmp && fabs(r_start - r_end) == 1)
        || (!is_whi && r_end == --r_tmp && fabs(r_start - r_end) == 1))
    {
      if ((p_end.get_color() != p.get_color() && p_end.get_type() != NONE)
          || en_passant)
      {
        //TODO delete pawn if there is a pawn with "en passant rules"
        return true;
      }
    }
  }
  return false;
}

bool GameEngine::check_rook_move(Move m)
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
      Piece p_tmp = actual_.get_piece(f_tmp, r_start);
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
      Piece p_tmp = actual_.get_piece(f_start, r_tmp);
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

bool GameEngine::check_knight_move(Move m)
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

bool GameEngine::check_bishop_move(Move m)
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
      Piece p_tmp = actual_.get_piece(f_tmp, r_tmp);
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

bool GameEngine::check_king_move(Move m, Piece p)
{
  Position::File f_start = m.start_get().file_get();
  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();

  if (fabs(f_end - f_start) <= 1 && fabs(r_end - r_start) <= 1)
  {
    std::cout << "toto" << std::endl;
    Position::File f = Position::ANNA;
    Position::Rank r = Position::EINS;
    while (r != Position::RANK_LAST)
    {
      Piece tmp = actual_.get_piece(f, r);
      if (tmp.get_type() != NONE && tmp.get_type() != KING
          && tmp.get_color() != p.get_color()
          && check_move(Move(Position(f, r), Position(f_end, r_end))))
        return false;
      ++f;
      if (f == Position::FILE_LAST)
      {
        std::cout << "new line" <<std::endl;
        f = Position::ANNA;
        ++r;
      }
    }
    return true;
  }
  else if (!actual_.has_king_moved(p.get_color()))
  {
    std::cout << "titi" <<std::endl;
    Position::File f_tmp = f_start;
    if (f_end > f_start)
      ++f_tmp;
    else
      --f_tmp;
    while (f_tmp != f_end)
    {
      Piece p_tmp = actual_.get_piece(f_tmp, r_start);
      if (p_tmp.get_type() != NONE)
        return false;
      Position::File f = Position::ANNA;
      Position::Rank r = Position::EINS;
      while (r != Position::RANK_LAST)
      {
        Piece tmp = actual_.get_piece(f, r);
        if (tmp.get_type() != NONE && tmp.get_type() != KING
            && tmp.get_color() != p.get_color()
            && check_move(Move(Position(f, r), Position(f_tmp, r_start))))
          return false;
      }
      ++f;
      if (f == Position::FILE_LAST)
      {
        f = Position::ANNA;
        ++r;
      }
    }
  }
  return false;
}

bool GameEngine::check_move(Move m)
{
  Piece p = actual_.get_piece_pos(m.start_get());

  //  Position::File f_start = m.start_get().file_get();
  //  Position::Rank r_start = m.start_get().rank_get();
  Position::File f_end = m.end_get().file_get();
  Position::Rank r_end = m.end_get().rank_get();

  Piece p_tmp = actual_.get_piece(f_end, r_end);
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
    return check_king_move(m, p);

  std::cout << m.start_get() << m.end_get() << std::endl;
  return false;
}


bool GameEngine::check_rules()
{
  return true;
}

void GameEngine::add_history(Chessboard cb)
{
  history_.push_back(cb);
}

void GameEngine::clear_history()
{
  history_.clear();
}

int GameEngine::is_finished()
{
  // Check is player mat ?

  // is player pat ?
  // is draw ?
  // is actual player disqualified ?
  // is actual player timeout ?
  return 0;
}
