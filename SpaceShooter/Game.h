#pragma once
#include "SFML\Graphics.hpp"

#include "MousePointer.h"

class Game
{
private:

	MousePointer mousePointer;
	

	bool quitGame = false;
	void QuitGame() { quitGame = true; }

public:
	Game();
	~Game();

	void Play(sf::RenderWindow& window);

	bool Quitting() { return quitGame; }

};

