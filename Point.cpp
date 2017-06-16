#include "Point.h"

/*
	Default constructor
*/
Point::Point(){
	x = 0;
	y = 0;
}

/*
	Constructor with params
	@param xPos, yPos, coords to set x and y to 
*/
Point::Point(int xPos, int yPos){
	x = xPos;
	y = yPos;
}

//Getters
int Point::getX(){
	return x;
}

int Point::getY() {
	return y;
}
