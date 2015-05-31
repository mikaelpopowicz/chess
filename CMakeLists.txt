cmake_minimum_required(VERSION 2.8)

# Project declaration
project(Chess)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++1y -pedantic")

# Generation of the source files list
file (
  GLOB_RECURSE
  source_files
  src/*
)

# Executable declaration
add_executable(
  chess
  ${source_files}
)
