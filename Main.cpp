#include "Dungeon.h"



int main() {

	std::cout << "////////////////////////////////////////////" << std::endl;
	std::cout << "/      Dungeon Map Generator Project       /" << std::endl;
	std::cout << "/    Author: Benedict Arterton 14046916    /" << std::endl;
	std::cout << "/      Oxford Brookes University 2017      /" << std::endl;
	std::cout << "////////////////////////////////////////////" << std::endl;

	
	//Initialise the seed for the Mersenne Twister PRNG
	MT::initSeed();

	//Create a Dungeon object
	Dungeon d = Dungeon();

	//Print the dungeon to console
	d.print();
	
	//Print the seeds the Dungeon was generated on
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Entered Seed = " << MT::getString() << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Current Seed = " << MT::getSeed() << std::endl;
	d.log();
	
	system("pause");
	return 0;
}