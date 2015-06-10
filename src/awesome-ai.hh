#ifndef AWESOME_AI_
# define AWESOME_AI_

# include "ai.hh"
# include "chessboard.hh"
# include <utility>

class AwesomeAi : public Ai
{
public:
  AwesomeAi(Color color);
  ~AwesomeAi();
  Move move_get();
  void print();
  const std::string& name_get() const;
  void last_opponent_move_set(const Move& last_opponent_move);

private:
  Chessboard board_;
  int nb_move_;
  std::string name_;
  int cpt_make_;
  int cpt_undo_;
  bool flag_;

  std::pair<int, Move> minimax(Color color, int step);
  Move make_white_opening();
  Move make_black_opening();

};

#endif /* AWESOME_AI_ */
