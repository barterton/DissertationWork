#pragma once
#include "Direction.h"
#include "Tiles.h"

class Cell { 
private:
	//tileType
	Tiles _tileType;
	//Coords
	int _x, _y;
	//Direction for a tile to be facing
	Direction _dir;

	bool walkable;
	//The roomID of a tile
	int _roomId;
	

public:
	//getters and setters
	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

	int getRoomID();
	void setRoomID(int roomId);

	Direction getDir();
	void setDir(Direction dir);

	bool getWalkable();
	void setWalkable(bool w);

	Tiles getTile();
	void setTile(Tiles tileType);

	//Default constructor and more detailed constructor
	Cell();
	Cell(int x, int y, Direction dir, Tiles tileType);
};