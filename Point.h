#pragma once

/*
	Class for storing coordinates of a point
*/
class Point {

private:
	//coords
	int x, y;

public:
	Point();
	Point(int xPos, int yPos);

	int getX();
	int getY();

};