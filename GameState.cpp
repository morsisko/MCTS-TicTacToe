#include "GameState.h"

std::random_device GameState::rd;
std::mt19937 GameState::g(GameState::rd());

player_indicator GameState::getBoardStateAt(coord x, coord y)
{
	return board[y * BOARD_SIZE + x];
}

void GameState::put(coord x, coord y)
{
	board[y * BOARD_SIZE + x] = currentTurn;
}

bool GameState::checkWinnerAfterMove(coord xx, coord yy)
{
	//CHECK HORIZONTAL WIN
	int horizontal = 0;
	for (coord x = xx + 1; x < BOARD_SIZE; x++)
	{
		if (getBoardStateAt(x, yy) != currentTurn)
			break;

		horizontal++;
	}

	for (coord x = xx - 1; x >= 0; x--)
	{
		if (getBoardStateAt(x, yy) != currentTurn)
			break;

		horizontal++;
	}

	if (horizontal >= TO_WIN - 1)
		return true;

	//CHECK VERTICAL WIN
	int vertical = 0;

	for (coord y = yy + 1; y < BOARD_SIZE; y++)
	{
		if (getBoardStateAt(xx, y) != currentTurn)
			break;

		vertical++;
	}

	for (coord y = yy - 1; y >= 0; y--)
	{
		if (getBoardStateAt(xx, y) != currentTurn)
			break;

		vertical++;
	}

	if (vertical >= TO_WIN - 1)
		return true;

	//CHECK DIAGONAL WIN
	int diagonal = 0;

	for (coord x = xx + 1, y = yy + 1; x < BOARD_SIZE && y < BOARD_SIZE; x++, y++)
	{
		if (getBoardStateAt(x, y) != currentTurn)
			break;

		diagonal++;
	}

	for (coord x = xx - 1, y = yy - 1; x >= 0 && y >= 0; x--, y--)
	{
		if (getBoardStateAt(x, y) != currentTurn)
			break;

		diagonal++;
	}

	if (diagonal >= TO_WIN - 1)
		return true;

	//CHECK ANTIDIAGONAL WIN
	int antidiagonal = 0;

	for (coord x = xx - 1, y = yy + 1; x >= 0 && y < BOARD_SIZE; x--, y++)
	{
		if (getBoardStateAt(x, y) != currentTurn)
			break;

		antidiagonal++;
	}

	for (coord x = xx + 1, y = yy - 1; x < BOARD_SIZE && y >= 0; x++, y--)
	{
		if (getBoardStateAt(x, y) != currentTurn)
			break;

		antidiagonal++;
	}

	if (antidiagonal >= TO_WIN - 1)
		return true;

	return false;
}

GameState::GameState()
{
	std::memset(board, NONE, sizeof(board));
}

bool GameState::canMoveHere(coord x, coord y)
{
	if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
		return false;

	if (winner != NONE)
		return false;

	return getBoardStateAt(x, y) == NONE;
}

bool GameState::isBoardFull()
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		if (board[i] == NONE)
			return false;

	return true;
}

std::vector<Move> GameState::getAllLegalMoves()
{
	std::vector<Move> moves;

	for (coord y = 0; y < BOARD_SIZE; y++)
		for (coord x = 0; x < BOARD_SIZE; x++)
			if (canMoveHere(x, y))
				moves.push_back(Move{ x, y });

	return moves;
}

void GameState::move(coord x, coord y)
{
	put(x, y);
	if (checkWinnerAfterMove(x, y))
		winner = currentTurn;

	else if (isBoardFull())
		winner = DRAW;

	if (currentTurn == PLAYER_X)
		currentTurn = PLAYER_O;

	else
		currentTurn = PLAYER_X;
}

void GameState::move(const Move & m)
{
	move(m.x, m.y);
}


player_indicator GameState::getWinner()
{
	return winner;
}

player_indicator GameState::getPreviousTurnIndicator()
{
	if (currentTurn == PLAYER_X)
		return PLAYER_O;

	return PLAYER_X;

}

player_indicator GameState::playRandomGame()
{
	if (getWinner() != NONE)
		return getWinner();

	std::vector<Move> allLegalMoves = getAllLegalMoves();

	std::shuffle(allLegalMoves.begin(), allLegalMoves.end(), g);

	for (auto& move : allLegalMoves)
	{
		this->move(move);
		if (getWinner() != NONE)
			break;
	}

	return getWinner();
}

GameState::~GameState()
{
}
