#include "stdafx.h"
#include "Game.h"
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


PlayerObject::PlayerObject() :
	GameObject::GameObject()
{
	// yeah yeah I know, magic numbers, bite me :p
	m_Body.setFillColor(sf::Color::Green);
	m_Body.setSize({ 50,20 });
	m_Body.setPosition({ 100, 200 });
	//m_Body.setOrigin({ m_Body.getSize().x / 2,m_Body.getSize().y / 2 });
	moveVec = sf::Vector2f(0,0);
}

void PlayerObject::Update(Game* game, float dt)
{
	
	Input(game, dt);

	if (moveVec.x != 0 && moveVec.y != 0)
	{
		moveVec *= .7071f;
	}
	m_Body.move(moveVec);
}

void PlayerObject::Input(Game* game, float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x = MOVESPEED * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveVec.x = -MOVESPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveVec.y = -MOVESPEED * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveVec.y = MOVESPEED * dt;
	}

	//mouse input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//magic numbers for now,
		//TODO: build the different levels of the weapons as they power up
		// stand in numbers are assumed for level 1 untill bigger system is in

		game->FireWeapon(dt, m_Body.getPosition()); 
	}

}

int WallObject::m_WallsCount = 0;

WallObject::WallObject(float height) :
	GameObject::GameObject()
{
	
	m_WallsCount++;
	m_Body.setFillColor(sf::Color::Color(40, 40, 40, 255));
	m_Body.setSize(sf::Vector2f(m_Width, height));
	int temp = m_WallsCount % 2;

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

void WallObject::Update(Game* game, float dt)
{
	m_Body.move(sf::Vector2f(-500*dt, 0));

	if (m_Body.getPosition().x < -200)
	{
		m_IsDestroyed = true;
	}
}

int WallObject::GetWallCount()
{
	return m_WallsCount;
}

BlasterBullet::BlasterBullet(int radius, int moveSpd, sf::Vector2f dir, sf::Vector2f location) :
	GameObject::GameObject()


{
	m_Body.setFillColor(sf::Color::Red);
	sf::Vector2f firingPosition(sf::Vector2f(location.x + 30, location.y));
	m_Body.setPosition(firingPosition);
	m_Body.setSize({ 10,10 });
	//m_Body.setOrigin(m_Body.getSize().x / 2, m_Body.getSize().y / 2);
	m_MoveSpeed = moveSpd;
	//m_Body.setRadius(radius);
	
	//m_MoveSpeed(moveSpd)
	//m_MoveDirection(dir)
	m_MoveDirection = dir;
	m_LifeTime = 0;
}

void BlasterBullet::Update(Game * game, float dt)
{
	
	m_Body.move(m_MoveDirection.x * m_MoveSpeed * dt, m_MoveDirection.y * m_MoveSpeed * dt);
	m_LifeTime += dt;
	if (m_LifeTime > 3)
	{
		m_IsDestroyed = true;
	}
}
