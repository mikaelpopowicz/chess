#ifndef AI_HH_
# define AI_HH_

# include <string>

# include "player/player.hh"

/*!
** \brief The interface of the artificial intelligence.
*/
class Ai: public Player
{
public:
  Ai(Color color);
  virtual ~Ai();

  /*!
  ** \brief Return the name of the group leader.
  **
  ** @return the group leader
  */
  virtual const std::string& name_get() const = 0;

protected:
  Color color_;
};

# include "ai.hxx"

#endif /* !AI_HH_ */
