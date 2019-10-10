#pragma once
#include <memory>
#include <algorithm>
#include "GameState.h"
#include <iostream>

class Node
{
private:
	GameState state;
	Node* parent = nullptr;
	std::vector<Move> allowedMoves;
	std::vector<std::unique_ptr<Node>> children;
	int played = 0;
	int wins = 0;

public:
	Node(GameState state);
	Node(GameState state, Move move, Node* parent);
	bool isFullyExpanded();
	bool isLeaf();
	bool hasParent();
	double getUCT();
	Node* getParent();
	Node* getBestChildren();
	Node* expand();
	player_indicator simulate();
	void update(player_indicator winner);
	Move getMostVisitedMove();
	void debugChildren();
	int getRealPlayed();
	~Node();
};

