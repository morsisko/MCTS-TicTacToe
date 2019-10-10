#include "Node.h"

Node::Node(GameState state)
{
	this->state = state;

	allowedMoves = this->state.getAllLegalMoves();
}

Node::Node(GameState state, Move move, Node * parent)
{
	this->state = state;
	this->parent = parent;

	this->state.move(move);

	if (this->state.getWinner() == NONE)
		allowedMoves = this->state.getAllLegalMoves();
}

bool Node::isFullyExpanded()
{
	return children.size() == allowedMoves.size();
}

bool Node::isLeaf()
{
	return children.empty();
}

bool Node::hasParent()
{
	return parent != nullptr;
}

double Node::getUCT()
{
	if (!played)
		return 0.0;

	return this->wins / (double)this->played + 1.42 * sqrt(log(parent->played) / this->played);
}

Node * Node::getParent()
{
	return parent;
}

Node * Node::getBestChildren()
{
	auto best = std::max_element(children.begin(), children.end(),
		[](const std::unique_ptr<Node>& left, const std::unique_ptr<Node>& right) {
		return left->getUCT() < right->getUCT();
	});

	return best->get();
}

Node * Node::expand()
{
	if (children.size() >= allowedMoves.size())
		return this; // It will be executed only if it's the end game node (no children)

	children.push_back(std::make_unique<Node>(state, allowedMoves[children.size()], this));
	return children.back().get();
}

player_indicator Node::simulate()
{
	if (state.getWinner() != NONE)
		return state.getWinner();

	GameState dummyState = state;
	return dummyState.playRandomGame();
}

void Node::update(player_indicator winner)
{
	played += 10;

	if (winner == state.getPreviousTurnIndicator())
		wins += 10;

	else if (winner == DRAW)
		wins += 5;

}

Move Node::getMostVisitedMove()
{
	auto best = std::max_element(children.begin(), children.end(),
		[](const std::unique_ptr<Node>& left, const std::unique_ptr<Node>& right) {
		return left->played < right->played;
	});

	int bestIndex = std::distance(children.begin(), best);

	return allowedMoves[bestIndex];
}

void Node::debugChildren()
{
	if (!isFullyExpanded())
	{
		std::cout << "This node isn't fully expanded" << std::endl;
		return;
	}

	for (int i = 0; i < children.size(); i++)
		std::cout << "Move: x: " << (int)allowedMoves[i].x << " y: " << (int)allowedMoves[i].y << " wins: " << children[i]->wins << " played: " << children[i]->played << std::endl;
}

int Node::getRealPlayed()
{
	return played / 10;
}


Node::~Node()
{
}
