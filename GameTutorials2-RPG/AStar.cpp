#include "stdafx.h"
#include "AStar.h"


AStar::AStar(Graph &graph)
	:graph(graph)
{

}

std::shared_ptr<std::list<graphNode*>> AStar::SolveAlgorithm(const sf::Vector2i& srcpos, const sf::Vector2i& targetpos)
{
	this->srcpos = srcpos;
	this->targetpos = targetpos;
	targetreached = false;
	std::list<graphNode*>* pq = new std::list<graphNode*>();
	std::unordered_set<graphNode*>* openSet = new std::unordered_set<graphNode*>();

	auto fCostcomparator = [](graphNode *leftnode, graphNode *rightnode)
	{
		return leftnode->fCost < rightnode->fCost;
	};
	
	graphNode *srcNode = &(graph.getNode(srcpos));
	srcNode->gCost = 0;
	graphNode* targetNode = &(graph.getNode(targetpos));
	srcNode->hCost = nodedistance(srcNode,targetNode);
	pq->emplace_back(srcNode);					//push node into queue.

	while (!pq->empty() && !targetreached) {		//while priority queue is not empty
		pq->sort(fCostcomparator);
		graphNode* curr = pq->front();
		pq->pop_front();								//pop from queue.
		curr->Visited = true;

		if (curr->nodeloc == targetpos) { //set target reached to true
			targetreached = true;
			continue;
		}

		for (auto &neighbour : curr->neighbours) {

			if (neighbour->Visited || neighbour->isObstacle) {
				
				continue;
			}
		
				double estimatedgCost = curr->gCost + nodedistance(curr, neighbour);
				if (estimatedgCost < neighbour->gCost) {			//if estiamted gcost is lesser, means there is a more optimal path from origin to th neighbour
					neighbour->parent = curr;
					neighbour->gCost = estimatedgCost;
					neighbour->hCost = nodedistance(neighbour, targetNode);
					neighbour->fCost = neighbour->gCost + neighbour->hCost;
					auto find = openSet->find(neighbour);
					if (find == openSet->end()) {		//if NOT in set
						pq->emplace_back(neighbour);
						openSet->insert(neighbour);
					}
				}
			
		}
	}
	return retracePath(srcNode, targetNode);
}

//void AStar::constructPath(Grid& grid)
//{
//	node* traverse = &graph.getNode(targetpos);
//	if (traverse != nullptr) {
//		while (traverse->parent != nullptr) {
//			traverse = traverse->parent;
//		}
//	}
//}


std::shared_ptr<std::list<graphNode*>> AStar::retracePath(graphNode* startNode, graphNode* endNode)
{
	std::shared_ptr<std::list<graphNode*>> path = std::make_shared<std::list<graphNode*>>();
	graphNode* currentNode = endNode;

	if (currentNode->parent)
	{
		while (currentNode != startNode) {
			path->push_back(currentNode);
			currentNode = currentNode->parent;
		}
		
		path->reverse();
	}
	else
	{
		std::cout << "Crisis averted" << std::endl;
	}

	graph.resetGraph();
	return path;
}

double AStar::nodedistance(graphNode* a, graphNode* b)
{
	int dx = (a->nodeloc.x - b->nodeloc.x);
	int dy= (a->nodeloc.y - b->nodeloc.y);
	return sqrt((dx * dx) + (dy * dy));			//sqrt(dx^2 - dy^2) for Euclidean	
}
