#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"


void Game::ObjectQuickSort(int left, int right)
{
	//outer indices of the list of objects
	// needed for the recursive call
	// need these temps iter values to also have initual values left and right
	int i = left;
	int j = right;

	int index = (left + right) / 2;
	float pivot = m_GameObjectsList[index]->GetXValue();
	// partition
	//as long as i is less than j
	// then left is still left of right, right?
	// find the ones out of place and move that bitch

	while (i <= j)
	{
		while (m_GameObjectsList[i]->GetXValue() < pivot)
		{
			i++;
		}
		while (m_GameObjectsList[j]->GetXValue() > pivot)
		{
			j--;
		}

		//switch around ones found to be in the wrong place
		if (m_GameObjectsList[i]->GetXValue() > m_GameObjectsList[j]->GetXValue())
		{
			GameObject* _temp = m_GameObjectsList[i];
			m_GameObjectsList[i] = m_GameObjectsList[j];
			m_GameObjectsList[j] = _temp;
			i++;
			j--;
			//delete _temp;
		}


	}

	if (left < j)
	{
		ObjectQuickSort(left, j);
	}
	if (i > right)
	{
		ObjectQuickSort(i, right);
	}
}

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

	//sort all Items by their x position. used for collision
	/*if (m_GameObjectsList.size() > 2)
	{
		ObjectQuickSort(0, m_GameObjectsList.size() - 1);
	}*/



	//update all objects
	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		m_GameObjectsList[i]->Update(&(*this), dt);

	}
	//TODO: add checks for collisions before destroying


	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		if (m_GameObjectsList[i]->IsDestroyed())
		{
			delete m_GameObjectsList[i];
			m_GameObjectsList.erase(m_GameObjectsList.begin() + i);
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

void Game::FireWeapon(float dt, sf::Vector2f pos)
{
	m_WeaponCountdown += dt;
	if (m_WeaponCountdown >= .12f)
	{
		m_WeaponCountdown = 0;

		int tempX = mousePointer.GetPosition().x - pos.x;
		int tempY = mousePointer.GetPosition().y - pos.y;

		float mag = sqrtf(((tempX * tempX) + (tempY * tempY)));
		sf::Vector2f unitDirection = sf::Vector2f(tempX / mag, tempY / mag);
		float unitMag = (tempX / mag) + (tempY / mag);

		//its magic! again! poof!
		AddObject(new BlasterBullet(5, 500, sf::Vector2f(tempX/mag, tempY / mag), pos));
	}
}
