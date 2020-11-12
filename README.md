# MCTS-TicTacToe
An AI TicTacToe implementation using Monte Carlo Tree Search written in C++ and SFML.

https://en.wikipedia.org/wiki/Monte_Carlo_tree_search

# Compiling
Tested on Windows and Linux using SFML 2.5
## Visual Studio
Open project, set correct SFML include and library path, build
## Makefile
If you installed your SFML in non-standard folder you need to edit the very first lines of Makefile to set correct SFML path. Otherwise just type `make` in your shell.

# Editing the code
You can change the board size or the "X" and "O" in a row to win using GameState.h lines 12 & 13

# Download
You can download the compiled binaries for Windows x64 on the 8x8 board playing to 5 points here: https://github.com/morsisko/MCTS-TicTacToe/releases/download/1.0v/Release.zip

![The game](https://i.imgur.com/gQkiD4E.png)
