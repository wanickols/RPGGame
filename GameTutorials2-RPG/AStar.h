#pragma once
#include "Graph.h"
#include <unordered_set>


class AStar {
public:
	AStar(Graph &graph);
	std::shared_ptr<std::list<graphNode*>> SolveAlgorithm(const sf::Vector2i& srcpos, const sf::Vector2i& targetpos);
	
private:
	Graph &graph;
	sf::Vector2i srcpos;
	sf::Vector2i targetpos;
	bool targetreached = false;
	std::shared_ptr<std::list<graphNode*>> retracePath(graphNode* startNode, graphNode* endNode);
	double nodedistance(graphNode* a, graphNode* b);
};

