inline bool Move::operator==(const Move& move) const
{
  return initial_ == move.start_get() && final_ == move.end_get();
}

inline std::ostream& operator<<(std::ostream& ostr, const Move& move)
{
  return ostr << "[" << move.start_get() << " -> " << move.end_get() << "]";
}
