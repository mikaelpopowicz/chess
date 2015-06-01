inline bool Chessboard::operator==(const Chessboard& chessboard) const
{
  for (int row = 0; row < 8; ++row)
    for (int col = 0; col < 8; ++col)
      if (board_[row][col] != chessboard.board_[row][col])
        return false;
  return true;
}
