#include "chessboard.hh"
#include "position.hh"
#include "color.hh"
#include "piece-type.hh"

#include <vector>

Chessboard::Chessboard()
  : white_king_moved_(false),
    black_king_moved_(false),
    white_king_(Position(Position::EVA, Position::EINS)),
    black_king_(Position(Position::EVA, Position::ACHT))
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
}

Chessboard::~Chessboard()
{
}

Piece Chessboard::get_piece_pos(const Position& p) const
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

  if (p.get_type() == NONE)
    return -1;

  //Move the piece
  board_[line_start][col_start] = Piece(NONE, BLACK);
  board_[line_end][col_end] = p;

  int res = 0;
  // If there is a promotion
  if (m.promotion_get() != NONE && p.get_type() == PAWN)
  {
    res = 1;
    board_[line_end][col_end].set_type(m.promotion_get());
  }

  // If the king is moved
  if (p.get_type() == KING)
  {
    bool king_moved = (p.get_color() == WHITE && white_king_moved_)
          || (p.get_color() == BLACK && black_king_moved_);

    // in case of a castling kingside
    if (!king_moved && m.end_get().file_get() == Position::GUSTAV)
    {
      // moving the rook
      board_[line_end][col_end - 1] = board_[line_end][7];
      board_[line_end][7] = Piece(NONE, BLACK);
      res = 2;
    }

    // in case of a castling queenside
    else if (!king_moved && m.end_get().file_get() == Position::CESAR)
    {
      //moving the rook
      board_[line_end][col_end + 1] = board_[line_end][0];
      board_[line_end][0] = Piece(NONE, BLACK);
      res = 3;
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

  return res;
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
