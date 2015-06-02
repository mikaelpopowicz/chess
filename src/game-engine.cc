#include "game-engine.hh"
#include <cmath>

GameEngine::GameEngine(Player* p1, Player* p2)
: p1_(p1),
  p2_(p2),
  previous_moved_(Position(Position::FILE_FIRST, Position::RANK_FIRST)),
  nb_turn_no_move_(0)
{
  history_.push_back(actual_);
}

GameEngine::~GameEngine()
{
  delete p1_;
  delete p2_;
}

/*void GameEngine::set_observer(Observer o)
{
}*/

int GameEngine::play()
{
  if (p1_ == NULL || p2_ == NULL)
    return -1;

  Color color_turn = p1_->color_get();
  //TODO o;notify_on_game_started();
  int status = 0;
  // While game not finished:
  while (status == 0)
  {
    actual_.print();
    //Get a move from the current Player
    if (color_turn == p1_->color_get())
    {
      actual_move_ = p1_->move_get();
      p2_->last_opponent_move_set(actual_move_);
    }
    else
    {
      actual_move_ = p2_->move_get();
      p1_->last_opponent_move_set(actual_move_);
    }

    //Check move & rules ok
    if (actual_.check_move(actual_move_, previous_moved_) == false)
    {
      //TODO o.notify_on_player_disqualified(color_turn)
      //TODO o.notify_on_game_finished()
      return 2;
    }

    Position end = actual_move_.end_get();
    //Check if piece taken
    Piece piece = actual_.get_piece_pos(actual_move_.start_get());
    Piece destination = actual_.get_piece_pos(end);

    Position pos(end.file_get(), actual_move_.start_get().rank_get());
    Piece& tmp = actual_.get_piece(pos.file_get(), pos.rank_get());
    bool en_passant = previous_moved_ == pos && tmp.get_type() == PAWN
      && ((tmp.get_color() == WHITE && pos.rank_get() == Position::VIER)
          || (tmp.get_color() == BLACK && pos.rank_get() == Position::FUNF));

    if (destination.get_type() != NONE || en_passant)
    {
      if (en_passant)
      {
        //TODO notify_on_piece_taken(tmp.get_type(), end);
      }
      else
      {
        //TODO notify_on_piece_taken(destination.get_type(), end);
      }
      clear_history();
    }
    //Make move
    int res = actual_.make_move(actual_move_);
    ++nb_turn_no_move_;
    add_history(actual_);
    previous_moved_ = actual_move_.end_get();
    if (res == 0 || res == 1)
    {
      //TODO notify_on_piece_moved(piece.get_type(), end);
      if (piece.get_type() == PAWN || destination.get_type() != NONE)
        nb_turn_no_move_ = 0;
    }
    if (res == 2)
    {
      //TODO notify_on_kingside_castling(color_turn)
      //TODO notify_on_piece_moved(KING, end)
      //TODO notify_on_piece_moved(ROOK, Position(end.file_get(),static_cast<Position::Rank>(end.rank_get() - 1)))
    }
    else if (res == 3)
    {
      //TODO notify_on_queenside_castling(color_turn)
      //TODO notify_on_piece_moved(KING, end)
      //TODO notify_on_piece_moved(ROOK, Position(end.file_get(),static_cast<Position::Rank>(end.rank_get() + 1)))
    }
    else if (res == 1)
    {
      //TODO notify_on_piece_promoted(actual_move_.promotion_get(), end);
    }

    //Check if player check

    if (color_turn == p1_->color_get())
      color_turn = p2_->color_get();
    else
      color_turn = p1_->color_get();

    status = is_finished(color_turn);
  }

  if (status == 3)
  {
    //TODO o.notify_on_draw()
  }

  //TODO o.notify_on_game_finished()
  return 0;
}

int GameEngine::is_finished(Color c)
{
  // Check is player mat ? for each king (white&black), find his possible
  // moves. if each move is controlled by a piece of another color, he's mat
  Position pos_king = actual_.get_king_pos(c);
  if (actual_.is_player_mat(pos_king, previous_moved_))
  {
    //TODO o.notify_on_player_mat...
    //if c = white, c'est 2 qui a gagné : return 2;
    if (c == WHITE)
      return 2;
    else
      return 1;
  }

  // is player pat ?
  if (actual_.is_player_pat(c, previous_moved_))
  {
    //TODO o.notify_on_player_pat(c)
    return 3;
  }

  // is draw ?
  if (nb_turn_no_move_ >= 50 || actual_.is_threefold_repetition(history_))
    return 3;

  // is actual player timeout ?
  return 0;
}


void GameEngine::add_history(Chessboard cb)
{
  history_.push_back(cb);
}

void GameEngine::clear_history()
{
  history_.clear();
}
