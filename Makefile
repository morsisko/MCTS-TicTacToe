PATH_TO_SFML_INCLUDE = .
PATH_TO_SFML_LIBS = .

CC = g++
SRC_DIR = .
SRCS    = $(wildcard $(SRC_DIR)/*.cpp)
THREADS = pthread
OUT_APP = TicTacToe
LIB_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

build:
	$(CC) $(SRCS) -$(THREADS) -I$(PATH_TO_SFML_INCLUDE) -L$(PATH_TO_SFML_LIBS) -o $(OUT_APP) $(LIB_FLAGS)
