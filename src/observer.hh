#ifndef OBSERVER_HH_
# define OBSERVER_HH_

# include <vector>
# include "listener.hh"
# include "color.hh"
# include "chessboard-interface.hh"
# include "position.hh"

class Observer
{
public:
  Observer();
  ~Observer();
  void add_observer(Listener* listener);
  std::vector<Listener*> get_listeners();

  void notify_register_chessboard_interface(const ChessboardInterface& chessboard_interface);
  void notify_on_game_started();
  void notify_on_game_finished();
  void notify_on_piece_moved(const PieceType& piece, const Position& from, const Position& to);
  void notify_on_piece_taken(const PieceType& piece, const Position& at);
  void notify_on_piece_promoted(const PieceType& piece, const Position& p);
  void notify_on_kingside_castling(const Color& color);
  void notify_on_queenside_castling(const Color& color);
  void notify_on_player_check(const Color& color);
  void notify_on_player_mat(const Color& color);
  void notify_on_player_pat(const Color& color);
  void notify_on_player_timeout(const Color& color);
  void notify_on_player_disqualified(const Color& color);
  void notify_on_draw();

private:
  std::vector<Listener*> listeners_;
};

#endif /* !OBSERVER_HH_ */
