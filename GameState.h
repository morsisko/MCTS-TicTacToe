#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <cstring>


typedef char player_indicator;
typedef char coord;

#define BOARD_SIZE 8
#define TO_WIN 5

#define NONE 0
#define PLAYER_X 1
#define PLAYER_O 2
#define DRAW 3

struct Move
{
	coord x;
	coord y;
};

class GameState
{
private:
	player_indicator board[BOARD_SIZE * BOARD_SIZE];
	player_indicator currentTurn = PLAYER_O;
	player_indicator winner = NONE;


	void put(coord x, coord y);
	bool checkWinnerAfterMove(coord x, coord y);
public:
	static std::random_device rd;
	static std::mt19937 g;

	GameState();
	player_indicator getBoardStateAt(coord x, coord y);
	bool canMoveHere(coord x, coord y);
	bool isBoardFull();
	std::vector<Move> getAllLegalMoves();
	void move(coord x, coord y);
	void move(const Move& m);
	player_indicator getWinner();
	player_indicator getPreviousTurnIndicator();
	player_indicator playRandomGame();

	~GameState();
};

