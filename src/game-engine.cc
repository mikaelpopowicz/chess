#include "game-engine.hh"

GameEngine::GameEngine(Player* p1, Player* p2)
  : p1_(p1),
    p2_(p2),
    nb_turn_no_move_(0)
{
  history_.push_back(actual_);
}

GameEngine::~GameEngine()
{
}

/*void GameEngine::set_observer(Observer o)
{
}*/

int GameEngine::play()
{
  //Begin the game
  //Color color_turn = WHITE;
  while (is_finished() == 0)
  {
  }

  // While game not finished:

  //Get a move from the Player 1
  //Check move & rules ok
  //Make move
  //Get a move from the Player 2
  //Check move & rules ok
  //Make move
  return 0;
}

bool GameEngine::check_move()
{
  Piece p = actual_.get_piece_pos(actual_move_.start_get());
  if (p.get_type() == PAWN)
  {
  }
  return true;
}

bool GameEngine::check_rules()
{
  return true;
}

void GameEngine::add_history(Chessboard cb)
{
  history_.push_back(cb);
}

void GameEngine::clear_history()
{
  history_.clear();
}

int GameEngine::is_finished()
{
  // Check is player mat ?
  
  // is player pat ?
  // is draw ?
  // is actual player disqualified ?
  // is actual player timeout ?
  return 0;
}
