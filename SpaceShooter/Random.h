#pragma once
#include <random>
#include <ctime>

class Random
{

	//declarations
	/*void Init();
	int IntInRange(int low, int high);
	float FloatInRange(float low, float high);*/


	//definitions
	//setting a random machine
	std::minstd_rand generater;

public:
	void Init()
	{
		//seeding with time
		generater.seed(static_cast<unsigned int>(time(NULL)));
	}

	// using suggested distribution methods for randoms
	int IntInRange(int low, int high)
	{
		std::uniform_int_distribution<int> distribution(low, high);
		return distribution(generater);
	}

	float FloatInRange(float low, float high)
	{
		std::uniform_real_distribution<float> distribution(low, high);
		return distribution(generater);
	}
};