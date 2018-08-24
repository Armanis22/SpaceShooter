#pragma once
#include "SFML\Graphics.hpp"
#include "Random.h"

class GameObject
{



public:
	GameObject();
	~GameObject() {};

	virtual void Update(float dt) {};
	virtual void Draw(sf::RenderWindow& window);

	bool IsDestroyed() { return m_IsDestroyed; }

protected:
	bool m_IsDestroyed;
	sf::RectangleShape m_Body;
};

class PlayerObject : public GameObject
{
private:
	//sf::RectangleShape m_Body;
	const float MOVESPEED = 300;
	const sf::Vector2f noMove = sf::Vector2f(0,0);
	sf::Vector2f moveVec;

public:
	PlayerObject();
	~PlayerObject() {};

	void Update(float dt);

	void Input(float dt);
};

class WallObject : public GameObject
{
private:
	const int m_Width = 100;
	const int m_MoveSpeed = 150;

public:
	static int m_WallsCount;
	WallObject(float height);

	void Update(float dt);
	int GetWallCount();

};