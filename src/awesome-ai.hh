#ifndef AWESOME_AI_
# define AWESOME_AI_

# include "ai.hh"
# include "chessboard.hh"

class AwesomeAi : public Ai
{
public:
  AwesomeAi(Color color);
  ~AwesomeAi();
  Move move_get();
  const std::string& name_get();

private:
  Chessboard board_;
  int nb_move_;
  std::string name_;
  Color color_;

  std::pair<int, Move> minimax(Color color, int step);
  std::Move make_white_opening();
  std::Move make_black_opening();

};

#endif /* AWESOME_AI_ */
