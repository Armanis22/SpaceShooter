#pragma once
#include "SFML\Graphics.hpp"

#include "MousePointer.h"
#include "GameObject.h"
#include "Random.h"

class Game
{
private:

	sf::Clock clock;
	std::vector<GameObject*> m_GameObjectsList;
	Random myRandomGen;
	float m_WallCreateCountdown;

	MousePointer mousePointer;
	

	bool quitGame = false;
	void QuitGame() { quitGame = true; }


public:
	Game();
	~Game();

	void Play(sf::RenderWindow& window);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void AddObject(GameObject* object);

	void CreateWalls(float dt);

	bool Quitting() { return quitGame; }

};

