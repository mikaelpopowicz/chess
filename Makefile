CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -g3

SRC_DIR ?= src
CK_DIR ?= check

SRC = main.cc chess-manager.cc option-parser.cc

OBJ := $(SRC:.cc=.o)
OBJ := $(addprefix $(SRC_DIR)/, $(OBJ))

opt: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o opt

clean:
	$(RM) all $(OBJ)
