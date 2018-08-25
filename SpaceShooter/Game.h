#pragma once
#include "SFML\Graphics.hpp"

#include "MousePointer.h"
#include "Random.h"
//#include "Utils.h"


class GameObject;

class Game
{
private:

	sf::Clock clock;
	std::vector<GameObject*> m_GameObjectsList;
	Random myRandomGen;

	float m_WallCreateCountdown;
	float m_WeaponCountdown;

	MousePointer mousePointer;
	

	bool	quitGame = false;
	void	QuitGame	() { quitGame = true; }


public:
	Game();
	~Game();

	void	Play		(sf::RenderWindow& window);
	void	Update		(float dt);
	void	Draw		(sf::RenderWindow& window);
	void	AddObject	(GameObject* object);

	void	CreateWalls	(float dt);
	void	FireWeapon	(float dt, sf::Vector2f pos);

	bool	Quitting	() { return quitGame; }
	Random	&GetNumGen	() { return myRandomGen; }
	void	ObjectQuickSort(int left, int right);
};

