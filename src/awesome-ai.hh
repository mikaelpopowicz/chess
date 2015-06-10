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

  std::pair<int, Move> minimax(Color color, int step);
  Move make_white_opening();
  Move make_black_opening();

};

AI_EXPORT(AwesomeAi)

#endif /* AWESOME_AI_ */
