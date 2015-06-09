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
  Piece& get_piece_pos(const Position& p);
  Piece get_piece(Position::File f, Position::Rank r) const;
  Piece& get_piece(Position::File f, Position::Rank r);
  /*!
  ** Make the move concerned and save it in a history.
  ** @return 0 if nothing exceptional happened (& move done)
  ** @return 1 if there is a promotion
  ** @return 2 if there's a kingside castling
  ** @return 3 if there's a queenside castling
  ** @return -1 if no move
  */
  int make_move(Move m);
  /*
  ** Undo the last move.
  ** @return true if the move is well canceled
  */
  bool undo();

  bool has_king_moved(Color c);
  Position get_king_pos(Color c);

  bool check_move(Move m);
  bool is_player_check(Position pos_king);
  bool is_player_mat(Position pos_king);
  bool is_player_pat(Color c);
  bool is_threefold_repetition(std::vector<Chessboard> history);

  void print();

  inline bool operator==(const Chessboard& chessboard) const;

  /*!
  ** Gives the list of the pieces' position corresponding to the color.
  */
  std::vector<Position> get_pieces(Color color);
  /*!
  ** This methods finds where the piece on the position pos_piece can go.
  ** @return the list of this reachable positions
  */
  std::vector<Position> get_possible_moves(Position pos_piece);

protected:
  Piece board_[SIZE][SIZE];
  bool white_king_moved_;
  bool black_king_moved_;
  Position white_king_;
  Position black_king_;
  Position previous_moved_;
  /*!
  ** This vector contains the positions of rooks which have not been moved
  ** since the begining of the game.
  */
  std::vector<Position> initial_rooks_;
  /*!
  ** This vector contains all the previous moves played.
  */
  std::vector<std::pair<Move, Piece>> history_;

  bool check_pawn_move(Move m, Piece p);
  bool check_rook_move(Move m);
  bool check_knight_move(Move m);
  bool check_bishop_move(Move m);
  bool check_king_move(Move m, Color c);
};

# include "chessboard.hxx"

#endif /*! CHESSBOARD_HH */
