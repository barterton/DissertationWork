#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <cstdio>

#include "Cell.h"
#include "Direction.h"
#include "Prng.h"
#include "Room.h"
#include "Tiles.h"
#include "Node.h"

/*
	Dungeon class, contains the majority of the code for this project, involving:
	Room placement and generation, route finding, distance calculations along with the dungeon map being stored in this class
	Some elements of his class could be moved into separate classes however, I did not want to do that
*/

class Dungeon {
private:

	//Counts for generated objects
	int generatedRooms = 0;
	int generatedDoors = 0;
	int generatedFeatures = 0;

	//Dimensions of the 2D array
	static int const _width = 75;
	static int const _height = 50;

	//vector for storing all the rooms
	std::vector<Room> roomList;

	//vectors for storing corridor and wall coords
	std::vector<Point> corridorList;
	std::vector<Point> wallList;

	//Vectors for storing the doors and features
	std::vector<Cell> doorList;
	std::vector<Cell> featureList;

	//vector for storing the connected doors
	std::vector<Point> connectedDoors;

	//2D array map 
	Cell map[_width][_height];

	//checks if x and y are in bounds of 2D array
	bool isValid(int x, int y);

	//Make a room 
	bool makeRoom(int x, int y, int id);

	//Place a shape/room
	bool placeShape(Tiles tile, Tiles wallTile, Room& room);

	//Create that shape on the map
	void makeShape(int x, int y, int w, int h, Tiles tile, Tiles wallTile);

	//Set a tile in the map
	void setTile(int x, int y, Tiles tile, bool walkable);

	//creates doors in all rooms 
	void createDoors();

	//create features in all rooms based on a probability
	void createFeatures(float prob);

	//Min distance between doors and corridor locations, calls findPath
	void minDistance();

	//Max distance between two doors, calls findPath
	void maxDoorDistance();

	//A*
	void findPath(Point startNode, Point endNode);

	//Get the neighbours and create objects of them for a given node
	std::vector<Node> getNeighbours(Node node);

	//Get a cell at coords x and y
	Cell getCell(int x, int y);

	//get whether a cell is walkable at x and y
	bool getWalkable(int x, int y);

	//get the distance between two nodes
	int getDistance(Node a, Node b);

	//Add walls to corridors neighbours
	void setCorridorWalls();

	//add padding around a room (UNUSED)
	void addRoomPadding();

public:
	//constructor
	Dungeon();

	Room getRoom(int n) { return roomList[n]; }

	void print();
	void log();

	//generate rooms
	void generate(int iter);
};