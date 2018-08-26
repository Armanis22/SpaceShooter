#pragma once
#include "SFML\Graphics.hpp"
#include "Random.h"

class StarBackground
{
private:

	struct MyStars
	{
		sf::CircleShape body;
		int radius;
		int moveSpeed;
	};

	Random starsRandom;
	std::vector<MyStars> starVec;
	float m_spawnCountdown;

	void CreateStar();
public:

	StarBackground();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

};