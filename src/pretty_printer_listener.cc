#include "pretty_printer_listener.hh"

PrettyPrinterListener::PrettyPrinterListener()
 : board_()
{}

PrettyPrinterListener::~PrettyPrinterListener()
{}

void PrettyPrinterListener::register_chessboard_interface(const ChessboardInterface& chessboard_interface)
{}

void PrettyPrinterListener::on_game_started()
{
  std::cout << "CA DEMARRRRRE" << std::endl;
}

void PrettyPrinterListener::on_game_finished()
{
  std::cout << "C FINIIIIIIIIIIIIIT" << std::endl;
}

void PrettyPrinterListener::on_piece_moved(const PieceType& piece, const Position& from,
                                      const Position& to)
{
  std::cout << "PIECE MOOOVEOVOEVO" << std::endl;
  PieceType type = piece;
  type = type;
  Position pos = from;
  pos = to;
}

void PrettyPrinterListener::on_piece_taken(const PieceType& piece, const Position& at)
{
  PieceType type = piece;
  type = type;
  Position pos = at;
  pos = pos;
}

void PrettyPrinterListener::on_piece_promoted(const PieceType& piece, const Position& p)
{
  PieceType type = piece;
  type = type;
  Position pos = p;
  pos = pos;
}

void PrettyPrinterListener::on_kingside_castling(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_queenside_castling(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_player_check(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_player_mat(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_player_pat(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_player_timeout(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_player_disqualified(const Color& color)
{
  Color c = color;
  c = c;
}

void PrettyPrinterListener::on_draw()
{}

LISTENER_EXPORT("Pretty printer", new PrettyPrinterListener());