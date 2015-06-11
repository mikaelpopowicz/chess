cmake_minimum_required(VERSION 2.8)

# Project declaration
project(Chess)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -O3 -std=c++1y -pedantic")

IF (UNIX)
  ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   cmake.check_cache
   *.cmake
   Makefile
   core core.*
   gmon.out
   *~
   CMakeFiles/
  )

  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
ENDIF(UNIX)

# Generation of the source files list
file (
  GLOB_RECURSE
  source_files
  src/observer.cc
  src/ai.cc
  src/player/player.cc
  src/player/player-abstract.cc
  src/player/player-pgn.cc
  src/player/player-human.cc
  src/piece.cc
  src/parser/parserPGN.cc
  src/parser/option-parser.cc
  src/move.cc
  src/game-engine.cc
  src/chess-manager.cc
  src/class-loader.cc
  src/chessboard-interface.cc
  src/chessboard.cc
  src/chessboard-adapter.cc
  src/listener.cc
  src/main.cc
  src/position.cc
)

# Executable declaration
add_executable(
  chess
  ${source_files}
)

add_library(
  ai
  SHARED
  src/player/player.cc
  src/ai.cc
  src/awesome-ai.cc
  src/move.cc
  src/position.cc
  src/chessboard.cc
)

target_link_libraries(
  chess
  -ldl
)

add_library(
  pretty-printer
  SHARED
  src/listener.hh
  src/chessboard-interface.cc
  src/chessboard-adapter.cc
  src/chessboard.cc
  src/pretty_printer_listener.cc
)
