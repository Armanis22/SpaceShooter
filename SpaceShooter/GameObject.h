#pragma once
#include "SFML\Graphics.hpp"
#include "Random.h"

extern class Game;

class GameObject
{



public:
	GameObject();
	~GameObject() {};

	virtual void Update(Game* game, float dt) {};
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

	void Update(Game* game, float dt);

	void Input(Game* game, float dt);
};

class WallObject : public GameObject
{
private:
	const int m_Width = 100;
	const int m_MoveSpeed = 150;

public:
	static int m_WallsCount;
	WallObject(float height);

	void Update(Game* game, float dt);
	int GetWallCount();

};

class BlasterBullet : public GameObject
{

private:
	int m_Radius;
	int m_MoveSpeed;
	sf::Vector2f m_MoveDirection;
	float m_Countdown = 0;
	
public:
	BlasterBullet(int radius, int moveSpd, sf::Vector2f dir, sf::Vector2f location);

	//sf::CircleShape m_Body;

	void Update(Game* game, float dt);
};