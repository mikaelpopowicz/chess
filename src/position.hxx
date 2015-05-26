inline Position::Position(File file, Rank rank)
  : file_ (file),
    rank_ (rank)
{
}

inline Position::Position()
{
}

inline Position& Position::operator=(const Position& position)
{
  file_ = position.file_;
  rank_ = position.rank_;

  return *this;
}

inline bool Position::operator==(const Position& position) const
{
  return file_ == position.file_ && rank_ == position.rank_;
}

inline bool Position::operator!=(const Position& position) const
{
  return !operator== (position);
}

inline Position::File Position::file_get() const
{
  return file_;
}

inline Position::Rank Position::rank_get() const
{
  return rank_;
}

inline Position::File operator++(Position::File& file)
{
  return file = static_cast<Position::File>(file + 1);
}

inline Position::File operator--(Position::File& file)
{
  return file = static_cast<Position::File>(file - 1);
}

inline Position::Rank operator++(Position::Rank& rank)
{
  return rank = static_cast<Position::Rank>(rank + 1);
}

inline Position::Rank operator--(Position::Rank& rank)
{
  return rank = static_cast<Position::Rank>(rank - 1);
}

inline std::ostream& operator<<(std::ostream& ostr, const Position& position)
{
  return ostr << static_cast<char>('a' - 1 + position.file_get())
	      << position.rank_get();
}
