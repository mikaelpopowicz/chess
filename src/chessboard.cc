#include "chessboard.hh"
#include "position.hh"
#include "color.hh"
#include "piece-type.hh"

#include <vector>

Chessboard::Chessboard()
  : king_moved_(false),
    left_rook_moved_(false),
    right_rook_moved_(false)
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

Piece Chessboard::get_piece_pos(Position p)
{
  return get_piece(p.file_get(), p.rank_get());
}

Piece Chessboard::get_piece(Position::File f, Position::Rank r)
{
  return board_[r - 1][f - 1];
}

bool Chessboard::make_move(Move m)
{
  Piece p = get_piece_pos(m.start_get());
  int line_start = m.start_get().rank_get() - 1;
  int col_start = m.start_get().file_get() - 1;
  int line_end = m.end_get().rank_get() - 1;
  int col_end = m.end_get().file_get() - 1;

  if (p.get_type() == NONE)
    return false;

  //Move the piece
  board_[line_start][col_start] = Piece(NONE, BLACK);
  board_[line_end][col_end] = p;

  // If there is a promotion
  if (m.promotion_get() != NONE && p.get_type() == PAWN)
  {
    board_[line_end][col_end].set_type(m.promotion_get());
  }

  // If the king is moved
  if (p.get_type() == KING)
  {
    king_moved_ = true;

    // in case of a castling kingside
    if (!king_moved_ && !right_rook_moved_
        && m.end_get().file_get() == Position::GUSTAV)
    {
      // moving the rook
      board_[line_end][col_end - 1] = board_[line_end][7];
      board_[line_end][7] = Piece(NONE, BLACK);
      right_rook_moved_ = true;
    }

    // in case of a castling queenside
    else if (!king_moved_ && !left_rook_moved_
             && m.end_get().file_get() == Position::CESAR)
    {
      //moving the rook
      board_[line_end][col_end + 1] = board_[line_end][0];
      board_[line_end][0] = Piece(NONE, BLACK);
      left_rook_moved_ = true;
    }
  }

  return true;
}

std::vector<Position> Chessboard::possible_moves_from(Position pos)
{
  Piece p = get_piece_pos(pos);
  std::vector<Position> moves;

  // Add simple moves
  if (p.get_type() == PAWN)
  {
    int way = 1;
    if (p.get_color() == BLACK)
      way = -1;
    moves.push_back(Position(pos.file_get(),
                    static_cast<Position::Rank>(pos.rank_get() + way)));
    // 2 cases if first move
    if ((p.get_color() == WHITE && pos.rank_get() == Position::ZWEI)
        || (p.get_color() == BLACK && pos.rank_get() == Position::SIEBEN))
      moves.push_back(Position(pos.file_get(),
                      static_cast<Position::Rank>(pos.rank_get() + way * 2)));
  }
  else if (p.get_type() == ROOK)
  {
    for (Position::Rank r = ++(pos.rank_get()); r < Position::RANK_LAST; ++r)
    {
      Piece tmp = get_piece(pos.file_get(), r);
      if (tmp.get_type() != NONE && tmp.get_color() == p.get_color())
        break;
      moves.push_back(Position(pos.file_get(), r));
      if (tmp.get_type() != NONE)
        break;
    }
  }
  else if (p.get_type() == KNIGHT)
  {
  }
  else if (p.get_type() == BISHOP)
  {
  }
  else if (p.get_type() == QUEEN)
  {
  }
  else if (p.get_type() == KING)
  {
  }
  // For each move, check if there's a piece of the same color on it

  return moves;
}
