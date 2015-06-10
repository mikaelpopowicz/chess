#include "observer.hh"
#include <iostream>

Observer::Observer()
{}

Observer::~Observer()
{
  for (Listener* listener : this->listeners_)
    delete listener;
}

void Observer::add_observer(Listener* listener)
{
  this->listeners_.push_back(listener);
}

std::vector<Listener*> Observer::get_listeners()
{
  return listeners_;
}

void Observer::notify_register_chessboard_interface(const ChessboardInterface& chessboard_interface)
{
  for (Listener* listener : this->listeners_)
    listener->register_chessboard_interface(chessboard_interface);
}

void Observer::notify_on_game_started()
{
  for (Listener* listener : this->listeners_)
    listener->on_game_started();
}

void Observer::notify_on_game_finished()
{
  for (Listener* listener : this->listeners_)
    listener->on_game_finished();
}

void Observer::notify_on_piece_moved(const PieceType& piece, const Position& from, const Position& to)
{
  for (Listener* listener : this->listeners_)
    listener->on_piece_moved(piece, from, to);
}

void Observer::notify_on_piece_taken(const PieceType& piece, const Position& at)
{
  for (Listener* listener : this->listeners_)
    listener->on_piece_taken(piece, at);
}

void Observer::notify_on_piece_promoted(const PieceType& piece, const Position& p)
{
  for (Listener* listener : this->listeners_)
    listener->on_piece_promoted(piece, p);
}

void Observer::notify_on_kingside_castling(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_kingside_castling(color);
}

void Observer::notify_on_queenside_castling(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_queenside_castling(color);
}

void Observer::notify_on_player_check(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_player_check(color);
}

void Observer::notify_on_player_mat(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_player_mat(color);
}

void Observer::notify_on_player_pat(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_player_pat(color);
}

void Observer::notify_on_player_timeout(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_player_timeout(color);
}

void Observer::notify_on_player_disqualified(const Color& color)
{
  for (Listener* listener : this->listeners_)
    listener->on_player_disqualified(color);
}

void Observer::notify_on_draw()
{
  for (Listener* listener : this->listeners_)
    listener->on_draw();
}
