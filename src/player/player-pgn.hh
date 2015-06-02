#ifndef PLAYER_PGN_HH_
# define PLAYER_PGN_HH_

# include "player.hh"
# include "../color.hh"
# include "../move.hh"
# include "../piece-type.hh"
# include "../position.hh"
# include <vector>
# include <string>
# include "player-abstract.hh"
# include "../chessboard.hh"

/*!
** \brief Chess manager (main)
*/
class PlayerPGN : public PlayerAbstract
{
public:
  PlayerPGN(Color color, std::vector<std::string> moves);
  ~PlayerPGN();

  /*!
  ** Set the last Move played by the opponent.
  */
  virtual void last_opponent_move_set(const Move& last_opponent_move);

  /*!
  ** Return the next Move to be played by the Player.
  */
  Move move_get();

  void setMoves(std::vector<std::string> moves);
  void print();

private:
  std::vector<std::string> moves_;
  std::vector<std::string>::iterator iterator;
  Chessboard board_;
  bool eat;

  Move little_rock();
  Move big_rock();
  bool is_emplacement(std::string c);
  PieceType get_piece_type(std::string raw_move, int& index);
  Position get_old_position(PieceType type, Position position,
      Position::File file_start, Position::Rank rank_start);

/*  Position find_old_pawn(Position pos_end, Position::File file_start,
                         Position::Rank rank_start);
  Position find_old_bishop(Position pos_end, Position::File file_start,
                          Position::Rank rank_start);
  Position find_old_king(Position pos_end, Position::File file_start,
                          Position::Rank rank_start);
  Position find_old_queen(Position pos_end, Position::File file_start,
                          Position::Rank rank_start);
  Position find_old_knight(Position pos_end, Position::File file_start,
                          Position::Rank rank_start);
  Position find_old_rook(Position pos_end, Position::File file_start,
                          Position::Rank rank_start);*/
};

#endif /* !PLAYER_PGN_HH_ */
