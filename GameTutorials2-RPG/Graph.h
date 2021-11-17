#pragma once

/*node struct*/
struct graphNode {
	graphNode(int posx, int posy) :nodeloc({ posx,posy }) {}	//construct location

	sf::Vector2i nodeloc;		//posx, posy of the node in gridspace
	bool Visited = false;
	graphNode* parent = nullptr;		//pointer to parent node
	bool isObstacle = false;	//is the node an obstacle?
	double hCost = INFINITY;				//heuristics for node (distance from current node to target).
	double gCost = INFINITY;				//heuristics for node (distance from start to curent node).
	double fCost;						//fCost
	std::vector<graphNode*> neighbours;			//store the vector of neigghbours for the node
};

/* graph class*/
class Graph{

private:
	std::vector<graphNode> nodes;			//all nodes in the graph
	int totalXTiles;
	int totalYTiles;

public:
	Graph(int GridSize);		//construct the graph
	graphNode& getNode(const sf::Vector2i& loc);
	void resetGraph();
};