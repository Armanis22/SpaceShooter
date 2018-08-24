#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{

}

void GameObject::Draw(sf::RenderWindow & window)
{
	window.draw(m_Body);
}


PlayerObject::PlayerObject()
{
	m_Body.setFillColor(sf::Color::Green);
	m_Body.setSize({ 50,20 });
	m_Body.setPosition({ 100, 200 });
	m_Body.setOrigin({ m_Body.getSize().x / 2,m_Body.getSize().y / 2 });
	printf("Called\n");

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
