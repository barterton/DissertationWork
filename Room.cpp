#include "Room.h"
#include <iostream>
#include <string>

/*
	Constructor for Room
	sets up most variables
*/
Room::Room(int x, int y, int id) {
	_id = id;
	_x = x;
	_y = y;
	_width = MT::randomInt(minRoomSize, maxRoomSize);
	_height = MT::randomInt(minRoomSize, maxRoomSize);

	centreX = x + _width / 2;
	centreY = y + _height / 2; 
}

/*
	Method to create a feature in a room
	@return t, Cell where feature has been created
*/
Cell Room::createFeature() {
	//Create the Cell object, with random x and y coords between height and width of the room
	Cell t = Cell(MT::randomInt(_x + 1, _x + _width - 2), MT::randomInt(_y + 1, _y + _height - 2), Direction::NORTH ,Tiles::FEATURE);

	//Return the tile
	return t;
}

/*
	Method to create a door in a room
	@Param dir, direction to create a door in the room
	@return c, Cell where a door has been created
*/
Cell Room::createDoor(Direction dir) {

	//Create the Cell object
	Cell c = Cell();

	c.setWalkable(true);

	//Switch case for the Directions setting the variables of the Cell accordingly
	switch (dir) {
	case Direction::NORTH:
		c.setX(centreX);
		c.setY(_y - 1);
		c.setDir(dir);
		c.setTile(Tiles::DOOR);
		c.setRoomID(_id);
		return c;
		break;

	case Direction::SOUTH:
		c.setX(centreX);
		c.setY(_y + _height);
		c.setDir(dir);
		c.setTile(Tiles::DOOR);
		c.setRoomID(_id);
		return c;
		break;

	case Direction::EAST:
		c.setX(_x + _width);
		c.setY(centreY);
		c.setDir(dir);
		c.setTile(Tiles::DOOR);
		c.setRoomID(_id);
		return c;
		break;

	case Direction::WEST:
		c.setX(_x - 1);
		c.setY(centreY);
		c.setDir(dir);
		c.setTile(Tiles::DOOR);
		c.setRoomID(_id);
		return c;
		break;
	}
}

/*
	All of the methods below are for getting and setting
	the class variables
*/
int Room::getX() { return _x; }
int Room::getY() { return _y; }

void Room::setX(int x) { _x = x; }
void Room::setY(int y) { _y = y; }

int Room::getDoorCount() { return doorCount; }
void Room::setDoorCount(int d) { doorCount = d; }

int Room::getRoomMin() { return minRoomSize; }
int Room::getRoomMax() { return maxRoomSize; }

int Room::getId() { return _id; }

int Room::getCentreX() { return centreX; }
int Room::getCentreY() { return centreY; }

int Room::getWidth() { return _width; }
int Room::getHeight() { return _height; }
