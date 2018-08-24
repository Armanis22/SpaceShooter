#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	myRandomGen.Init();
	AddObject(new PlayerObject);
}


Game::~Game()
{
}

void Game::Play(sf::RenderWindow& window)
{

	
	//printf("%d\n", dt.asSeconds());

	while (window.isOpen())
	{
	sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!window.isOpen())
		{
			QuitGame();
		}
		
		//updating game app and objects.
		
		Update(dt.asSeconds());

		//updating the mouse position

		mousePointer.Update(sf::Mouse::getPosition(window));

		//start of window drawing stuff
		window.clear();

		Draw(window);

		window.draw(mousePointer.InnerTarget());
		window.draw(mousePointer.OuterTarget());

		window.display();
	}

}

void Game::Update(float dt)
{
	CreateWalls(dt);

	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		m_GameObjectsList[i]->Update(dt);
	}
	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		if (m_GameObjectsList[i]->IsDestroyed())
		{
			//delete m_GameObjectsList[i];
			m_GameObjectsList.erase(m_GameObjectsList.begin() + 1);
			i--;
		}
	}

}

void Game::Draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		m_GameObjectsList[i]->Draw(window);
	}
}

void Game::AddObject(GameObject * object)
{

	m_GameObjectsList.emplace_back(object);
}

void Game::CreateWalls(float dt)
{
	m_WallCreateCountdown += dt;
	if (m_WallCreateCountdown >= .09)
	{
		m_WallCreateCountdown = 0;

		//random height in a set, still messing with these
		AddObject(new WallObject(myRandomGen.FloatInRange(60,120)));
	}
}
