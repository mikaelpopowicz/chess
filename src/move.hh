#ifndef MOVE_HH_
# define MOVE_HH_

# include <iostream>

# include "piece-type.hh"
# include "position.hh"

/*!
** \brief A piece move.
**
** A rock move is represented by the movement of the king. The move of the rook
** is implicit, it is bound to the king move.
**
** Note that this class actually represents a ply.
*/
class Move
{
  public:
    Move();
    Move(const Position& initial, const Position& final,
         PieceType promotion = NONE);

    const Position& start_get() const;

    const Position& end_get() const;

    PieceType promotion_get() const;

    inline bool operator==(const Move& move) const;

  protected:
    Position initial_;
    Position final_;
    PieceType promotion_;
};

inline std::ostream& operator<<(std::ostream& ostr, const Move& move);

# include "move.hxx"

#endif /* !MOVE_HH_ */
