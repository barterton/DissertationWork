#pragma once
#include <vector>
#include <iostream>

#include "Point.h"

/*
	A class for use during route finding, stores gCost and hCost variables as well as
	ancestor nodes for all the previously visited nodes
*/

class Node {

private:
	//coords
	int x, y;

	//gCost and hCost
	int gCost;
	int hCost;

	std::vector<Point> ancestors;

public:
	//Default constructor
	Node() {}
	Node(int xPos, int yPos);

	static bool contains(std::vector<Node> n, Point p);

	//getters and setters
	int getX();
	int getY();

	int getHcost();
	void setHcost(int h);

	int getGcost();
	void setGcost(int g);

	int getFcost();

	//Ancestor opperations / previous nodes
	void setAncestors(std::vector<Point> a);
	std::vector<Point> getAncestors();
	std::vector<Point> returnAncestors();
};