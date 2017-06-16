#include "Cell.h"

// Default constructor
Cell::Cell() {
	_tileType = Tiles::UNUSED;
}

// Detailed Constructor
Cell::Cell(int x, int y, Direction dir, Tiles tileType) {
	_x = x;
	_y = y;
	_dir = dir;
	_tileType = tileType;
}


// X AND Y getters
int Cell::getX(){ 
	return _x; 
}

int Cell::getY(){ 
	return _y; 
}

// X AND Y Setters
void Cell::setX(int x){ 
	_x = x; 
}
void Cell::setY(int y) { 
	_y = y; 
}

//ID getter
int Cell::getRoomID(){
	return _roomId;
}

//ID Setter
void Cell::setRoomID(int id){
	_roomId = id;
}

//Direction
Direction Cell::getDir() { 
	return _dir; 
}

void Cell::setDir(Direction dir) { 
	_dir = dir; 
}

//Visited
bool Cell::getWalkable(){ 
	return walkable; 
}

void Cell::setWalkable(bool w){ 
	walkable = w;
}

//Tile character
Tiles Cell::getTile(){ 
	return _tileType; 
}

void Cell::setTile(Tiles tileType){
	_tileType = tileType; 
}
