#ifndef PRETTY_PRINTER_LISTENER_
# define PRETTY_PRINTER_LISTENER_

# include "listener.hh"
# include "chessboard.hh"
# include "move.hh"
# include "chessboard-adapter.hh"

class PrettyPrinterListener : public Listener
{
public:
  PrettyPrinterListener();
  ~PrettyPrinterListener();
  void register_chessboard_interface(const ChessboardInterface& chessboard_interface);
  void on_game_started();
  void on_game_finished();
  void on_piece_moved(const PieceType& piece, const Position& from,
                      const Position& to);
  void on_piece_taken(const PieceType& piece, const Position& at);
  void on_piece_promoted(const PieceType& piece, const Position& p);
  void on_kingside_castling(const Color& color);
  void on_queenside_castling(const Color& color);
  void on_player_check(const Color& color);
  void on_player_mat(const Color& color);
  void on_player_pat(const Color& color);
  void on_player_timeout(const Color& color);
  void on_player_disqualified(const Color& color);
  void on_draw();

private:
  Chessboard board_;
  ChessboardAdapter adapter_;
};

#endif /* PRETTY_PRINTER_LISTENER_ */
