#ifndef CHESSBOARD_HH
# define CHESSBOARD_HH

# include "piece.hh"
# include "move.hh"
# include "position.hh"
# include <vector>

# define SIZE 8

class Chessboard
{
public:
  Chessboard();
  virtual ~Chessboard();

  Piece get_piece_pos(const Position& p) const;
  Piece get_piece(Position::File f, Position::Rank r) const;
  Piece& get_piece(Position::File f, Position::Rank r);
  /*!
  ** Make the move concerned.
  ** @return 0 if nothing exceptional happened (& move done)
  ** @return 1 if there is a promotion
  ** @return 2 if there's a kingside castling
  ** @return 3 if there's a queenside castling
  ** @return -1 if no move
  */
  int make_move(Move m);

  bool has_king_moved(Color c);
  Position get_king_pos(Color c);

  bool check_move(Move m, Position previous_moved, bool is_test);
  bool is_player_check(Position pos_king, Position previous_moved);
  bool is_player_mat(Position pos_king, Position previous_moved);
  bool is_player_pat(Color c, Position previous_moved);
  bool is_threefold_repetition(std::vector<Chessboard> history);

  void print();

  inline bool operator==(const Chessboard& chessboard) const;

protected:
  Piece board_[SIZE][SIZE];
  bool white_king_moved_;
  bool black_king_moved_;
  Position white_king_;
  Position black_king_;

  bool check_pawn_move(Move m, Piece p, Position previous_moved,
                       bool is_test);
  bool check_rook_move(Move m);
  bool check_knight_move(Move m);
  bool check_bishop_move(Move m);
  bool check_king_move(Move m, Color c, Position previous_moved);
};

# include "chessboard.hxx"

#endif /*! CHESSBOARD_HH */
