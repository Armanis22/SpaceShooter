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
	float GetXValue() {	return m_Body.getPosition().x; }

	float GetLowY() { return m_Body.getPosition().y; }
	float GetHightY() { return m_Body.getPosition().y + m_Body.getSize().x; }

	const sf::RectangleShape& GetBody() { return m_Body; }

	GameObject operator<(const GameObject& other)
	{
		if ((this->m_Body.getPosition().x) > (other.m_Body.getPosition().x))
		{
			return *this;
		}
		else
		{
			return other;
		}

	}

protected:
	bool m_IsDestroyed;
	sf::RectangleShape m_Body;
};

class PlayerObject : public GameObject
{
private:
	const float MOVESPEED = 300;
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
	static int m_WallsCount;

public:
	WallObject(float height);
	~WallObject() {};
	void Update(Game* game, float dt);
	int GetWallCount();

};

class EnemyBaseObject :public GameObject
{
private:


public:
	


};

class BlasterBullet : public GameObject
{

private:
	int m_Radius;
	int m_MoveSpeed;
	sf::Vector2f m_MoveDirection;
	float m_LifeTime;

	
public:
	BlasterBullet(int radius, int moveSpd, sf::Vector2f dir, sf::Vector2f location);
	~BlasterBullet() {};
	//sf::CircleShape m_Body;

	void Update(Game* game, float dt);
};