#include "stdafx.h"
#include "GameObject.h"
//#include "Random.h"


GameObject::GameObject()
{
	m_IsDestroyed = false;
}

void GameObject::Draw(sf::RenderWindow & window)
{
	window.draw(m_Body);
}


PlayerObject::PlayerObject()
{
	// yeah yeah I know, magic numbers, bite me :p
	m_Body.setFillColor(sf::Color::Green);
	m_Body.setSize({ 50,20 });
	m_Body.setPosition({ 100, 200 });
	m_Body.setOrigin({ m_Body.getSize().x / 2,m_Body.getSize().y / 2 });

}

void PlayerObject::Update(float dt)
{
	Input(dt);

	if (moveVec.x != 0 && moveVec.y != 0)
	{
		moveVec *= .7071f;
	}
	m_Body.move(moveVec);
}

void PlayerObject::Input(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x = MOVESPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveVec.x = -MOVESPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveVec.y = -MOVESPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveVec.y = MOVESPEED * dt;
	}

}

int WallObject::m_WallsCount = 0;

WallObject::WallObject(float height)
{
	m_WallsCount++;
	m_Body.setFillColor(sf::Color::Color(40, 40, 40, 255));
	m_Body.setSize(sf::Vector2f(m_Width, height));
	int temp = m_WallsCount % 2;
	printf("%i\n", temp);
	//magic numbers I know
	// so we check if the number of walls is even or odd
	//odd ones go on the bottom to populate both
	//leaving the origin the same and jsut offsetting by the height for collision
	if (temp == 0)
	{
		m_Body.setPosition(sf::Vector2f(1300, 0));
	}
	else
	{
		m_Body.setPosition(sf::Vector2f(1200, (720 - height)));

	}
	
}

void WallObject::Update(float dt)
{
	m_Body.move(sf::Vector2f(-500*dt, 0));

	if (m_Body.getPosition().x < -150)
	{
		m_IsDestroyed = true;
	}
}

int WallObject::GetWallCount()
{
	return m_WallsCount;
}
