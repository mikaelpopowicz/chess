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
  PieceType get_piece_type(std::string raw_move, int index);
  Position get_old_position(PieceType type, std::pair<std::string, std::string> new_pos,
    std::string first_prev_emplacement, std::string second_prev_emplacement);

  Position find_old_pawn(std::pair<std::string, std::string> new_pos,
                         std::string f_prev, std::string s_prev);
  Position find_old_bishop(std::pair<std::string, std::string> new_pos,
                           std::string f_prev, std::string s_prev);
  Position find_old_king(std::pair<std::string, std::string> new_pos,
                         std::string f_prev, std::string s_prev);
  Position find_old_queen(std::pair<std::string, std::string> new_pos,
                          std::string f_prev, std::string s_prev);
  Position find_old_knight(std::pair<std::string, std::string> new_pos,
                           std::string f_prev, std::string s_prev);
  Position find_old_rook(std::pair<std::string, std::string> new_pos,
                         std::string f_prev, std::string s_prev);
};

#endif /* !PLAYER_PGN_HH_ */
