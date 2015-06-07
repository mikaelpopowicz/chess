#ifndef AWESOME_AI_
# define AWESOME_AI_

# include "ai.hh"
# include "chessboard.hh"

class AwesomeAi : public Ai
{
public:
  AwesomeAI(Color color);
  ~AwesomeAI();

private:
  Chessboard board_;
};

#endif /* AWESOME_AI_ */