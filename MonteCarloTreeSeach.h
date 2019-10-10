#pragma once
#include "Node.h"
#include <memory>
#include <Windows.h>

class MonteCarloTreeSeach
{
private:
	Node* selection();
	Node* expansion(Node* node);
	player_indicator simulation(Node* node);
	void backpropagation(Node* node, player_indicator winner);
	std::unique_ptr<Node> root;
public:
	MonteCarloTreeSeach();
	Move findBestMoveFor(GameState* gameState);
	~MonteCarloTreeSeach();
};

