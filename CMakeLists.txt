cmake_minimum_required(VERSION 2.8)

# Project declaration
project(Chess)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++1y -pedantic")

# Generation of the source files list
file (
  GLOB_RECURSE
  source_files
  src/main.cc
  src/parser/parserPGN.cc
  src/parser/option-parser.cc
  src/player.cc
  src/player-pgn.cc
  src/chess-manager.cc
  src/color.cc
  src/move.cc
  src/piece-type.cc
  src/position.cc
)

# Executable declaration
add_executable(
  chess
  ${source_files}
)
