#ifndef POSITION_HH_
# define POSITION_HH_

# include <ostream>

/*!
** \brief A position on the chessboard.
**
*/
class Position
{
public:
  /*!
  ** A column index on the chessboard.
  */
  enum File
  {
    FILE_FIRST,

    ANNA,
    BELLA,
    CESAR,
    DAVID,
    EVA,
    FELIX,
    GUSTAV,
    HECTOR,

    FILE_LAST
  };

  /*!
  ** A line index on the chessboard.
  */
  enum Rank
  {
    RANK_FIRST,

    EINS,
    ZWEI,
    DREI,
    VIER,
    FUNF,
    SECHS,
    SIEBEN,
    ACHT,

    RANK_LAST
  };

public:
  inline Position();

  inline Position(File file, Rank rank);

  virtual ~Position();

  inline Position& operator=(const Position& position);

  inline bool operator==(const Position& position) const;

  inline bool operator!=(const Position& position) const;

  inline File file_get() const;

  inline Rank rank_get() const;

protected:
  File file_;
  Rank rank_;
};

inline std::ostream& operator<<(std::ostream& ostr, const Position& position);

# include "position.hxx"

#endif /* !POSITION_HH_ */
