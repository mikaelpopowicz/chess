#include "pretty_printer_listener.hh"

PrettyPrinterListener::PrettyPrinterListener()
  : adapter_(Chessboard())
{}

PrettyPrinterListener::~PrettyPrinterListener()
{}

void PrettyPrinterListener::register_chessboard_interface(const ChessboardInterface& chessboard_interface)
{}

void PrettyPrinterListener::on_game_started()
{
  board_.print();
}

void PrettyPrinterListener::on_game_finished()
{}

void PrettyPrinterListener::on_piece_moved(const PieceType& piece, const Position& from,
                                      const Position& to)
{
  board_.make_move(Move(from, to));
  board_.print();
}

void PrettyPrinterListener::on_piece_taken(const PieceType& piece, const Position& at)
{}

void PrettyPrinterListener::on_piece_promoted(const PieceType& piece, const Position& p)
{}

void PrettyPrinterListener::on_kingside_castling(const Color& color)
{}

void PrettyPrinterListener::on_queenside_castling(const Color& color)
{}

void PrettyPrinterListener::on_player_check(const Color& color)
{}

void PrettyPrinterListener::on_player_mat(const Color& color)
{
  Color c = color;
  //c = c;
}

void PrettyPrinterListener::on_player_pat(const Color& color)
{}

void PrettyPrinterListener::on_player_timeout(const Color& color)
{}

void PrettyPrinterListener::on_player_disqualified(const Color& color)
{}

void PrettyPrinterListener::on_draw()
{}

LISTENER_EXPORT("Pretty printer", new PrettyPrinterListener());
