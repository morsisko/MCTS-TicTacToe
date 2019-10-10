#include "MonteCarloTreeSeach.h"



Node * MonteCarloTreeSeach::selection()
{
	Node* currentNode = root.get();

	while (currentNode->isFullyExpanded() && !currentNode->isLeaf())
		currentNode = currentNode->getBestChildren();

	return currentNode;
}

Node * MonteCarloTreeSeach::expansion(Node* node)
{
	return node->expand();
}

player_indicator MonteCarloTreeSeach::simulation(Node * node)
{
	return node->simulate();
}

void MonteCarloTreeSeach::backpropagation(Node * node, player_indicator winner)
{
	Node* currentNode = node;

	while (currentNode != nullptr)
	{
		currentNode->update(winner);
		currentNode = currentNode->getParent();
	}
}

MonteCarloTreeSeach::MonteCarloTreeSeach()
{
}

Move MonteCarloTreeSeach::findBestMoveFor(GameState* gameState)
{
	root = std::make_unique<Node>(*gameState);

	int start = GetTickCount();

	while (GetTickCount() - start < 3 * 1000)
	{
		Node* bestNode = selection();
		Node* expanded = bestNode->expand();
		player_indicator simulationWinnder = expanded->simulate();
		backpropagation(expanded, simulationWinnder);
	}

	root->debugChildren();

	Move bestMove = root->getMostVisitedMove();
	std::cout << "Best move - x: " << (int)bestMove.x << " y: " << (int)bestMove.y << std::endl << std::endl << std::endl;
	std::cout << "Total played: " << root->getRealPlayed() << std::endl;

	return bestMove;
}


MonteCarloTreeSeach::~MonteCarloTreeSeach()
{
}
