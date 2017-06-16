#pragma once
#include <random>
#include <chrono>
#include <iostream>
#include <string>

/*
	Pseudorandom number generation namespace
*/
namespace MT {

	//Initialise a seed
	void initSeed();

	//Get the entered seed string
	std::string getString();

	//Get the value of the seed entered
	unsigned int getSeed();

	//Get a random int up to max
	int randomInt(int max);

	//get a random int between a min and max
	int randomInt(int min, int max);

	//get a boolean based on a probability
	bool randomBoolean(double probability);
}