#pragma once
#include "SFML\Graphics.hpp"

class GameObject
{



public:
	GameObject();
	~GameObject() {};

	virtual void Update(float dt) {};
	virtual void Draw(sf::RenderWindow& window);

protected:
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
	void Draw(sf::RenderWindow& window) { window.draw(m_Body); }

	void Input(float dt);
};