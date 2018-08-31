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
	void DestroyObject() { m_IsDestroyed = true; }


	virtual float GetLowXValue() const { return m_Body.getPosition().x; }
	virtual float GetHighXValue() { return m_Body.getPosition().x + m_Body.getSize().x; }
	virtual float GetLowY() { return m_Body.getPosition().y; }
	virtual float GetHightY() { return m_Body.getPosition().y + m_Body.getSize().x; }

	virtual const sf::RectangleShape& GetBody() { return m_Body; }

	
	bool operator<(const GameObject& obj) const;

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

	void MovePlayer(sf::RectangleShape rect);
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

	float tester() { return m_Body.getPosition().x; }

	float GetLowXValue() const { 
		float temp = m_Body.getPosition().x;
		//printf("%f\n", temp);
		return temp; }
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