#pragma once
#include "Prng.h"
#include "Direction.h"
#include "Cell.h"


class Room {
private:
	int _x, _y; //Top left corner coords of the room
	int _width, _height;
	int _id;
	int centreX, centreY;

	//How many doors are in the room
	int doorCount;

	//Constraints for the minimum and maximum dimensions for a room
	static const int minRoomSize = 3;
	static const int maxRoomSize = 6;

public:
	//Constructor
	Room(int x, int y, int id);

	//Create a feature in the room (not a door)
	Cell createFeature();

	//Create a door feature in the room
	Cell createDoor(Direction dir);

	void setX(int x);
	void setY(int y);

	//getters and setters
	int getDoorCount();
	void setDoorCount(int d);

	int getRoomMin();
	int getRoomMax();

	int getId();

	int getX();
	int getY();

	int getCentreX();
	int getCentreY();

	int getWidth(); 
	int getHeight();
};