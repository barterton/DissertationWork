#include "Dungeon.h"

/*
	Constructor for the Dungeon, calls all the methods
*/
Dungeon::Dungeon() {

	//Fill dungeon with empty tiles
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {

			//Cells are constructed with Unused char type
			Cell c = Cell();
			c.setX(x);
			c.setY(y);
			c.setWalkable(true);

			//Add Cell to the map
			map[x][y] = c;
		}
	}

	//Allow the user to choose how many iterations of the generate method to run
	int iter;
	std::cout << "#######################################################################" << std::endl;
	std::cout << "# IMPORTANT Due to the brute forcing of room placement                #" << std::endl;
	std::cout << "#######################################################################" << std::endl;
	std::cout << "# If you enter less than 10 iterations, the dungeon will generate for #" << std::endl;
	std::cout << "# 10 iterations regardless                                            #" << std::endl;
	std::cout << "#######################################################################" << std::endl;
	std::cout << "# If you would like a large number of rooms iterate 1000 times        #" << std::endl;
	std::cout << "# If you would like around 10 rooms iterate 50 times                  #" << std::endl;
	std::cout << "# If you would like around 5 rooms iterate around 10 times            #" << std::endl;
	std::cout << "#######################################################################" << std::endl;
	std::cout << std::endl;
	std::cout << "How many iterations of the room generation method would you like to do? ";
	std::cin >> iter;

	//Call the generate method with iter passed as a parameter,
	generate(iter);

	//Print the Room infomation
	std::cout << "-----------------------------" << std::endl;
	for (int x = 0; x < roomList.size(); x++) {
		std::cout << "Room ID: " << getRoom(x).getId() << " Centre: " << getRoom(x).getCentreX() << "," << getRoom(x).getCentreY() << std::endl;
	}
	std::cout << "-----------------------------" << std::endl;

	//Print the door information
	for (int x = 0; x < doorList.size(); x++) {
		std::cout << " Room ID: " << doorList[x].getRoomID() << " Door ID: " << x << " Door COORD " << "{" << doorList[x].getX() << "," << doorList[x].getY() << "}" << std::endl;
	}
	std::cout << "-----------------------------" << std::endl;

	//Calculate the max distance between all the doors
	//Finds the route between the max points
	maxDoorDistance();

	//Set all connected doors locations tiles back to doors
	for (int x = 0; x < connectedDoors.size(); x++) {
		setTile(connectedDoors[x].getX(), connectedDoors[x].getY(), Tiles::DOOR, false);
	}

}

/*
	Method for printing the dungeon to the console
*/
void Dungeon::print() {
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			//getCell is a method that returns the cell at x, y
			if (getCell(x, y).getTile() == Tiles::UNUSED) { //Unused
				std::cout << ".";
			}
			else if (getCell(x, y).getTile() == Tiles::WALL) { //Wall
				std::cout << '#';
			}
			else if (getCell(x, y).getTile() == Tiles::FLOOR) { //Floor
				std::cout << ' ';
			}
			else if (getCell(x, y).getTile() == Tiles::FEATURE) {
				std::cout << '!';
			}
			else if (getCell(x, y).getTile() == Tiles::DOOR) {
				std::cout << '+';
			}
			else if (getCell(x, y).getTile() == Tiles::CORRIDOR) {
				std::cout << ' ';
			}
			else if (getCell(x, y).getTile() == Tiles::ROOM_PADDING) {
				std::cout << '.';
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << generatedRooms << " " << "Rooms Generated" << std::endl;
	std::cout << generatedDoors << " " << "Doors Generated" << std::endl;
	std::cout << generatedFeatures << " " << "Features Generated" << std::endl;
}

/*
	Method for logging the printed dungeon to a txt file, mainly used for debugging 
	purposes
*/
void Dungeon::log() {
	
	std::ofstream myfile;

	myfile.open("DungeonLog.txt", std::ios::out | std::ios::app);
	
	for (int y = 0; y < _height; y++) {
		if (y < 10) {
			myfile << y << "  ";
		}
		else {
			myfile << y  << " ";
		}
		for (int x = 0; x < _width; x++) {
			if (getCell(x, y).getTile() == Tiles::UNUSED) { //Unused
				myfile << ".";
			}
			else if (getCell(x, y).getTile() == Tiles::WALL) { //Wall
				myfile << '#';
			}
			else if (getCell(x, y).getTile() == Tiles::FLOOR) { //Floor
				myfile << ' ';
			}
			else if (getCell(x, y).getTile() == Tiles::FEATURE) { //Border
				myfile << '!';
			}
			else if (getCell(x, y).getTile() == Tiles::DOOR) {
				myfile << '+';
			}
			else if (getCell(x, y).getTile() == Tiles::CORRIDOR) {
				myfile << ' ';
			}
			else if (getCell(x, y).getTile() == Tiles::ROOM_PADDING) {
				myfile << '.';
			}
		}
		myfile << "\n";
	}
	myfile << "\n-------------------------\n";
	myfile.close();
}

/*
	Method for setting a tile type at x, y and whether it is walkable
	@param x, y, map coordinates to set tile at
	@param tile, tile type to set to
	@param walkable, whether a tile can be walked on or not
*/
void Dungeon::setTile(int x, int y, Tiles tile, bool walkable) {
	//If x and y are in bounds
	if (isValid(x, y)) {
		map[x][y].setTile(tile);
		map[x][y].setWalkable(walkable);
	}
}

/*
	Method for making a room
	@param x, y, coord to place room
	@param id, id with which room will be made
	@return true if room can be made, false if not
*/
bool Dungeon::makeRoom(int x, int y, int id) {
	//Create
	Room room = Room(x, y, id);

	//If placeShape is true
	if (placeShape(Tiles::FLOOR, Tiles::WALL, room)) {
		//Store room and return true
		roomList.push_back(room);
		return true;
	}
	else {
		return false;
	}
}


/*
	Method for placing a shape on the 2D array map
	@param tile, tileType to fill the shape with
	@param wallTile, tileType to outline the shape with
	@param, &room, reference to room being placed
	@return false if area is occupied or out of bounds, true otherwise
*/
bool Dungeon::placeShape(Tiles tile, Tiles wallTile, Room& room) {
	//Does not allow a room to be placed 4 tiles from the edge of the map in all directions
	if (room.getX()-3 < 1 || room.getY()-3 < 1 || (room.getX() + room.getWidth() + 3) > _width - 3 || (room.getY() + room.getHeight() + 3) > _height - 3) {
		return false; //Out of bounds
	}

	//Does not allow a room to be placed 3 tiles away both x and y from any other room
	for (int y = room.getY()-2; y < room.getY() + room.getHeight()+2; y++) {
		for (int x = room.getX()-2; x < room.getX() + room.getWidth()+2; x++) {
			if (getCell(x, y).getTile() != Tiles::UNUSED) {
				return false; //the area is already occupied
			}
		}
	}
	//loop the height of the shape + wall borders - 1 and + 1 in each direction
	makeShape(room.getX(), room.getY(), room.getWidth(), room.getHeight(), tile, wallTile);
}

/*
	Method for creating the shape on the map
	@param x, y, coords to place the room
	@param w, h, width and height of the room to be placed
	@param tile, wallTile, fill tileType and border tileType to create the shape with
*/
void Dungeon::makeShape(int x, int y, int w, int h, Tiles tile, Tiles wallTile) {
	//loop the height of the shape + wall borders - 1 and + 1 in each direction
	for (int j = y - 1; j < y + h + 1; j++) {
		//loop the width of the shape
		for (int i = x - 1; i < x + w + 1; i++) {
			if (i == x - 1 || j == y - 1 || i == x + w || j == y + h) {
				//Place wall around the shape of the room being placed
				//wallList.push_back(Point(i, j));//For room padding, not used currently
				setTile(i, j, wallTile, false);
			}
			else {
				//Fill floor space with the parameter tile type
				setTile(i, j, tile, false);
			}
		}
	}
}

/*
	Method for checking if a coordinate is a valid position
	@param x, y, coordinates to check
*/
bool Dungeon::isValid(int x, int y) {
	if (x < 1 || y < 1 || x > _width - 1 || y > _height - 1) {
		return false;
	}
	else {
		return true;
	}
}

/*
	Method for creating features in a room
	@param prob, probability of creating a feature
*/
void Dungeon::createFeatures(float prob) {
	for (int n = 0; n < generatedRooms; n++) {
		//If probability is true then create a new feature
		if (MT::randomBoolean(prob)) {
			generatedFeatures++;
			//Add the created feature for each room to the featureList
			featureList.push_back(getRoom(n).createFeature());
		}
	}
	for (int n = 0; n < featureList.size(); n++) {
		//Set the tiles in the map
		setTile(featureList[n].getX(), featureList[n].getY(), Tiles::FEATURE, false);
	}
}

/*
	Method for creating doors 
*/
void Dungeon::createDoors() {

	for (int n = 0; n < generatedRooms; n++) {

		//Booleans to prevent doors being placed on the same direction wall
		bool north = true;
		bool south = true;
		bool east = true;
		bool west = true;

		//Randomise the number of doors per room between 1 and 4
		int numberDoors = MT::randomInt(1, 4);

		for (int x = 0; x < numberDoors; x++) {

			//Randomise the direction to place a door
			int direction = MT::randomInt(4);

			//Increment the number of doors after each case provided the direction is availible
			switch (direction) {
			case 0:
				if (north) {
					doorList.push_back(getRoom(n).createDoor(Direction::NORTH));
					north = false;
					generatedDoors++;
				}
				break;
			case 1:
				if (south) {
					doorList.push_back(getRoom(n).createDoor(Direction::SOUTH));
					south = false;
					generatedDoors++;
				}
				break;
			case 2:
				if (east) {
					doorList.push_back(getRoom(n).createDoor(Direction::EAST));
					east = false;
					generatedDoors++;
				}
				break;
			case 3:
				if (west) {
					doorList.push_back(getRoom(n).createDoor(Direction::WEST));
					west = false;
					generatedDoors++;
				}
				break;
			}
		}
	}
	//Set the tiles of door locations to be doors
	for (int i = 0; i < doorList.size(); i++) {
		setTile(doorList[i].getX(), doorList[i].getY(), Tiles::DOOR, true);
	}
}

/*
	Method for calculating the maximum distance between all of the door locations
	This method is used to create the first corridor between the two doors of the
	greatest distance from each other
*/
void Dungeon::maxDoorDistance() {
	double max = 0;

	//Convert to POINTS
	Point startPoint, endPoint;

	int startID = 0, endID = 0;

	
	//Nested for loop to compare each door to each other
	for (int i = 0; i < doorList.size(); i++) {
		for (int j = 0; j < doorList.size(); j++) {

			//If both doors are not from the same room
			if (doorList[i].getRoomID() != doorList[j].getRoomID()) {

				//If the distance between the first door and the second door is greater than the current maximum
				if (getDistance(Node(doorList[i].getX(), doorList[i].getY()), Node(doorList[j].getX(), doorList[j].getY())) > max) {

					//The maximum now equals the new distance
					max = getDistance(Node(doorList[i].getX(), doorList[i].getY()), Node(doorList[j].getX(), doorList[j].getY()));

					//Set the startPoint x and y coords
					startPoint = Point(doorList[i].getX(), doorList[i].getY());

					//Set the endPoint x and y coords
					endPoint = Point(doorList[j].getX(), doorList[j].getY());

					//Set the values of the startID and endID
					startID = i;
					endID = j;
				}
			}
		}
	}

	//Find a path between the max points
	findPath(startPoint, endPoint);

	//Output the value of the max
	std::cout << "MAX: " << max << std::endl;
	std::cout << std::endl;

	//Add the doors with the max distance between them to the connected doors vector
	connectedDoors.push_back(endPoint);

	//Remove the door from the door list at the start point
	doorList.erase(doorList.begin() + startID);
	//Remove the door from the door list at the end point - 1, because a value has already been removed
	doorList.erase(doorList.begin() + endID-1);
	
	
	//Run the minDistance method
	minDistance();
}

/*
	Calculate the minimum distance between all the door locations and the corridor locations
	to determine where to create routes
*/
void Dungeon::minDistance() {

	//Initialise the min to a high value
	float min = 999;
	int index = 0;

	Point start, end;

	//While there are unconnected doors
	while (!doorList.empty()) {

		min = 999;

		//Nested for loop, loop all the corridors for all the doors
		for (int i = 0; i < doorList.size(); i++) {
			for (int j = 0; j < corridorList.size(); j++) {

				//If the distance between the door and corridor location is less than the minimum
				if (getDistance(Node(doorList[i].getX(), doorList[i].getY()), Node(corridorList[j].getX(), corridorList[j].getY())) < min) {
					//Set the min to the new distance
					min = getDistance(Node(doorList[i].getX(), doorList[i].getY()), Node(corridorList[j].getX(), corridorList[j].getY()));

					//Set the index to i
					index = i;

					//Set the start and end points
					start = Point(doorList[i].getX(), doorList[i].getY());
					end = corridorList[j];
				}
			}
		}
		//Remove the index/start door chosen
		doorList.erase(doorList.begin() + index);

		//Find a path between the start and end points 
		findPath(start, end);

		//Set the corridors to have walls
		setCorridorWalls();

		//Output the minimum
		std::cout << "MIN: " << min << std::endl;
		std::cout << std::endl;

		
	}
	
}

/* 
	A* (star) route finding, finds the shortest route between the startNode and the endNode
	@param startNode, starting point
	@param endNode, end point
*/
void Dungeon::findPath(Point startNode, Point endNode) {

	//Print the route creating
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Creating route between: " << "[" << startNode.getX() << "," << startNode.getY() << "] and [" << endNode.getX() << "," << endNode.getY() << "]" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::endl;

	//Add the startNode to the connectedDoors vector
	connectedDoors.push_back(startNode);

	//openSet of nodes
	std::vector<Node> openSet;
	//closedSet of nodes
	std::vector<Node> closedSet;

	//Convert start and end points to nodes
	Node origin = Node(startNode.getX(), startNode.getY());
	Node targetNode = Node(endNode.getX(), endNode.getY());
	
	//Set the gCost of the origin to 0 and add it to the openSet
	origin.setGcost(0);
	openSet.push_back(origin);


	bool found = false;

	int count = 0;

	//While route has not been found
	while (!found) {

		for (int i = 0; i < openSet.size(); i++) {

			//Set the currentNode to the first val in the OpenSet
			Node currentNode = openSet[0];

			//For all values in the openSet, choose the currentNode based on the lowest Fcost or if Fcosts are equal then lowest Hcost
			//Fcosts are the Gcosts + the Hcost
			for (int n = 0; n < openSet.size(); n++) {
				if (openSet[n].getFcost() < currentNode.getFcost() || openSet[i].getFcost() == currentNode.getFcost() && openSet[i].getHcost() < currentNode.getHcost()) {
					currentNode = openSet[n];
					count = n;
				}
			}
			//Remove the current node from the openSet
			openSet.erase(openSet.begin() + count);
			//Reset the count for the iter
			count = 0;

			//For each neighbour of the currentNode
			for each(Node neighbour in getNeighbours(currentNode)) {

				//If the neighbour node is walkable
				if (getWalkable(neighbour.getX(), neighbour.getY())) {

					//If the closed set does not contain the neighbour already
					if (!Node::contains(closedSet, Point(neighbour.getX(), neighbour.getY()))){

						//Calculate the new move to the neighbour from the current node
						int moveToNeighbour = currentNode.getGcost() + getDistance(currentNode, neighbour);

						//If the new move is less than the neighbours current Gcost, or the openSet doesn't contain it already
						if (moveToNeighbour < neighbour.getGcost() || !Node::contains(openSet, Point(neighbour.getX(), neighbour.getY()))) {
							//Set the neighbours gCost to the newMove cost, set ancestors to the currentNodes ancestors and set the Hcost of that node to the target
							neighbour.setGcost(moveToNeighbour);
							neighbour.setAncestors(currentNode.getAncestors());
							neighbour.setHcost(getDistance(neighbour, targetNode));

							//If the openSet does not contain the neighbour already, add it to the openSet
							if (!Node::contains(openSet, Point(neighbour.getX(), neighbour.getY()))) {
								openSet.push_back(neighbour);
							}
						}
					}
				}
			}
			//add the currentNode to the closedSet
			closedSet.push_back(currentNode);

			//If the currentNode is the target then route has been found
			if (currentNode.getX() == targetNode.getX() && currentNode.getY() == targetNode.getY()) {

				found = true;

				std::cout << "Found path to end node" << std::endl;
				
				//Loop for the currentNodes ancestor nodes 
				for (int i = 0; i < currentNode.returnAncestors().size(); i++) {
					//Add the tile to the corridor location vector
					corridorList.push_back(Point(currentNode.returnAncestors()[i].getX(), currentNode.returnAncestors()[i].getY()));
					//Set the tile to a corridor
					setTile(currentNode.returnAncestors()[i].getX(), currentNode.returnAncestors()[i].getY(), Tiles::CORRIDOR, true);
					
				}
				break;
			}
		}
	}
}

/*
	Method for setting the walls of the corridor tiles uses the 
	getNeighbours method to work out what cells are adjacent
*/
void Dungeon::setCorridorWalls() {
	for (int n = 0; n < corridorList.size(); n++) {
		//get the neighbours of the corridor tile
		for each (Node neighbour in getNeighbours(Node(corridorList[n].getX(), corridorList[n].getY()))) {
			//If they are of tileType unused then set them to wall
			if (getCell(neighbour.getX(), neighbour.getY()).getTile() == Tiles::UNUSED) {
				setTile(neighbour.getX(), neighbour.getY(), Tiles::WALL, true);
			}
		}
	}
}

/*
	Method for adding padding to rooms, unused as it causes many unresolved bugs at present
*/
void Dungeon::addRoomPadding() {
	for (int n = 0; n < wallList.size(); n++) {
		for each (Node neighbour in getNeighbours(Node(wallList[n].getX(), wallList[n].getY()))) {
			if (getCell(neighbour.getX(), neighbour.getY()).getTile() == Tiles::UNUSED) {
				std::cout << "Padding" << std::endl;
				setTile(neighbour.getX(), neighbour.getY(), Tiles::ROOM_PADDING, false);
			}
		}
	}
	for (int n = 0; n < doorList.size(); n++) {
		for each (Node neighbour in getNeighbours(Node(doorList[n].getX(), doorList[n].getY()))) {
			if (getCell(neighbour.getX(), neighbour.getY()).getTile() == Tiles::ROOM_PADDING) {
				std::cout << "REMOVED PADDING FOR DOOR" << std::endl;
				setTile(neighbour.getX(), neighbour.getY(), Tiles::UNUSED, true);
			}
		}
	}
}

/*
	Method for getting the Cell of a map at the x and y coordinates
	@param x, y, coordinates to get the Cell at
	@return Cell at map[x][y]
*/
Cell Dungeon::getCell(int x, int y) {
	return map[x][y];
}

/*
	Method for checking if a tile is walkable
	@param x, y, coordinates to check if walkable at
	@return boolean depending on the tile stored at coord x, y
*/
bool Dungeon::getWalkable(int x, int y){
	return map[x][y].getWalkable();
}

/*
	Method for getting the distance between two nodes 
	@param x, y, nodes to getDistance between
	@return the distance between two nodes
*/
int Dungeon::getDistance(Node x, Node y){

	//abs distance on the straight line
	int distanceX = std::abs(x.getX() - y.getX());
	int distanceY = std::abs(x.getY() - y.getY());

	if (distanceX > distanceY) {
		return 14 * distanceY + 10 * (distanceX - distanceY);
	}
	else {
		return 14 * distanceX + 10 * (distanceY - distanceX);
	}
}

/*
	Method of getting the neighbours of a given node
	@param node, node to get the neighbours for
	@return a vector of all the nieghbours locations
*/
std::vector<Node> Dungeon::getNeighbours(Node node){

	std::vector<Node> neighbours;

	//For the four directions in which neighbours can be reached
	//If the node is within the bounds of the map dimensions
	//Add it to neighbours vector

	//NORTH
	if (isValid(node.getX(), node.getY() - 1)) {
		neighbours.push_back(Node(node.getX(), node.getY() - 1));
	}
	//EAST
	if (isValid(node.getX() + 1, node.getY())) {
		
		neighbours.push_back(Node(node.getX() + 1, node.getY()));
	}
	//SOUTH
	if (isValid(node.getX(), node.getY() + 1)) {

		neighbours.push_back(Node(node.getX(), node.getY() + 1));
	}
	//WEST
	if (isValid(node.getX() - 1, node.getY())) {

		neighbours.push_back(Node(node.getX() - 1, node.getY()));
	}

	return neighbours;
}

/*
	Method to generate the rooms, doors and features
	@param iter, number of iterations to try and place rooms
*/
void Dungeon::generate(int iter) {

	int iterations = iter;

	//Generate x and y coords from the seed
	int x = MT::randomInt(0, _width);
	int y = MT::randomInt(0, _height);

	//Prevents iterations being lower than 10
	if (iter < 10) {
		iterations = 10;
	}

	for (int i = 0; i < iterations; i++) {
		//If the room can be made
		if (makeRoom(x, y, i)) {
			generatedRooms++;
			//Re-randomise the x and y coordinates
			x = MT::randomInt(0, _width);
			y = MT::randomInt(0, _height);
		}
		else {
			//randomise the x and y again
			x = MT::randomInt(0, _width);
			y = MT::randomInt(0, _height);
		}
	}
	//Create doors and features 
	createDoors();
	createFeatures(0.75);
	
}