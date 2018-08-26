#include "stdafx.h"
#include "StarBackground.h"

void StarBackground::CreateStar()
{
	MyStars tempStar;
	tempStar.radius = starsRandom.IntInRange(1, 5);
	tempStar.body.setRadius(tempStar.radius);
	tempStar.body.setFillColor(sf::Color::White);
	tempStar.moveSpeed = 200 - (tempStar.radius * 20);

	tempStar.body.setPosition(1250, starsRandom.IntInRange(10, 710));


	starVec.push_back(tempStar);
}

StarBackground::StarBackground()
{
	for (int i = 0; i < 10; i++)
	{
		CreateStar();
	}

}

void StarBackground::Update(float dt)
{
	m_spawnCountdown += dt;
	if (m_spawnCountdown > .10f)
	{
		m_spawnCountdown = 0;
		CreateStar();
	}

	for (int i = 0; i < starVec.size(); i++)
	{
		starVec[i].body.move(-starVec[i].moveSpeed * dt, 0);
		if (starVec[i].body.getPosition().x < -10)
		{
			starVec.erase(starVec.begin() + i);
		}
	}
}

void StarBackground::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < starVec.size(); i++)
	{
		window.draw(starVec[i].body);
	}
}
