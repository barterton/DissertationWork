#include "Prng.h"

namespace MT {

	std::mt19937 mt;
	std::string str;

	/*
		Method to setup the seed of the Mersenne Twister
	*/
	void initSeed() {
		//Setup clock to init the seed with time if neccessary
		typedef std::chrono::high_resolution_clock myclock;
		myclock::time_point beginning = myclock::now();

		std::string check;

		std::cout << "Would you like to manually enter a seed? y/n " << std::endl;
		std::getline(std::cin, check);

		if (check == "y") {

			std::cout << "Please, enter a seed: ";
			std::getline(std::cin, str);

			//seed the MT19937 with the entered string
			std::seed_seq seed1(str.begin(), str.end());
			mt.seed(seed1);

		}
		else {
			//Otherwise seed the MT19937 using time based 2nd seed
			myclock::duration d = myclock::now() - beginning;
			unsigned seed2 = d.count();
			mt.seed(seed2);
		}
		
	}

	//getters
	std::string getString() {
		return str;
	}
	unsigned int getSeed() {
		return mt();
	}

	/*
		Method to return a randomised number up to the parameter
		@param max, randomise a number between 0 and this parameter value
		@return a random number based on seed and the max
	*/
	int randomInt(int max) {
		//Create a new distribution between 0 and max
		std::uniform_int_distribution<> dist(0, max - 1);
		//pass the mt into dist and return
		return dist(mt);
		
	}

	/*
		Method to return a random number between two values
		@param min, max, bounds to create a random number between
		@return return a random number between min and max
	*/
	int randomInt(int min, int max) {
		std::uniform_int_distribution<> dist(min, max);
		return dist(mt);
	}

	/*
		Method to return true or false based on a probability
		@param probability, the probability that the method will return true
		@return true or false based on probability
	*/
	bool randomBoolean(double probability) {
		//Bernoulli distribution has two possible outcomes n = 0 or, n = 1(success) which occurs with probability p 
		std::bernoulli_distribution dist(probability);
		return dist(mt);
	}
}