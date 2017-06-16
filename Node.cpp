#include "Node.h"

//Constructor
Node::Node(int xPos, int yPos) {
	x = xPos;
	y = yPos;
	gCost = 999;
}

/*
	Method checks through a vector of Nodes for point p
	@param n, vector of nodes to check
	@param p, point to check if it exists in vector n
	@return true if p exists in n else false
*/
bool Node::contains(std::vector<Node> n, Point p){

	for (int i = 0; i < n.size(); i++) {
		//If p exists in n 
		if (n[i].getX() == p.getX() && n[i].getY() == p.getY()) {
			return true;
		}
	}
	return false;
}
//getters and setters
int Node::getX() {
	return x;
}

int Node::getY() {
	return y;
}

int Node::getHcost(){
	return hCost;
}

void Node::setHcost(int h){
	hCost = h;
}

int Node::getGcost() {
	return gCost;
}

void Node::setGcost(int g) {
	gCost = g;
}

int Node::getFcost(){
	return gCost + hCost;
}

/*
	Method to add the Point x and y to the ancestors vector 
	and return it
	@return the ancestors vector
*/
std::vector<Point> Node::getAncestors(){
	ancestors.push_back(Point(x, y));
	return ancestors;
}

/*
	Get the ancestors of the node and return them
	@return ancestors
*/
std::vector<Point> Node::returnAncestors(){
	return ancestors;
}

/*
	Method to set the ancestors to the parameter
	@param a, vector to set ancestors to
*/
void Node::setAncestors(std::vector<Point> a){
	ancestors = a;
}

