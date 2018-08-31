#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"



bool Game::CheckYValues(float num, float othernum)
{
	if (num > othernum)
		return true;
	return false;
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
	// send the fps to the console, I might change this
	// to an actual SFML obj in the corner. meh
	
	/*fpsCooldown += dt;
	if (fpsCooldown > 1.f)
	{
		fpsCooldown = 0;
		printf("%f\n", 1.0f / dt);
	}*/
	
	CreateWalls(dt);

	//sort all Items by their x position. used for collision
	if (m_GameObjectsList.size() > 2)
	{
		ObjectQuickSort(0, m_GameObjectsList.size() - 1);
		//std::sort(m_GameObjectsList.begin(), m_GameObjectsList.end());
	}



	//update all objects
	for (int i = 0; i < m_GameObjectsList.size(); i++)
	{
		//GetXMaybe(*m_GameObjectsList[i]);
		//printf("%f\n", m_GameObjectsList[i]->GetBody().getPosition().x);
		m_GameObjectsList[i]->Update(&(*this), dt);

		//collisions

		//welcome to my super nested, ultra ugly, craptastic collisions!
		int j = i + 1;
		if (j < m_GameObjectsList.size())
		{
			float temp;
			float iright = m_GameObjectsList[i]->GetBody().getPosition().x + 
							m_GameObjectsList[i]->GetBody().getSize().x;
			float jleft = m_GameObjectsList[j]->GetBody().getPosition().x;

			//for (; iright > jleft;j++)
			if (iright > jleft)
			{
				jleft = m_GameObjectsList[j]->GetBody().getPosition().x;
				float itop = m_GameObjectsList[i]->GetBody().getPosition().y;
				float jbottom = m_GameObjectsList[j]->GetBody().getPosition().y +
					m_GameObjectsList[j]->GetBody().getSize().y;
				if (itop < jbottom)
				{
					float ibottom = m_GameObjectsList[i]->GetBody().getPosition().y +
						m_GameObjectsList[i]->GetBody().getSize().y;
					float jtop = m_GameObjectsList[j]->GetBody().getPosition().y;
					if (ibottom > jtop)
					{
						if (dynamic_cast<PlayerObject*>(m_GameObjectsList[i]))
						{

							printf("called\n");
						}
					}
				}
				j++;

			}

		}
		

	}
	//TODO: add checks for collisions before destroying


	// delete objects and erase them from the vector
	for (size_t i = 0; i < m_GameObjectsList.size(); i++)
	{
		if (m_GameObjectsList[i]->IsDestroyed())
		{
			delete m_GameObjectsList[i];
			m_GameObjectsList.erase(m_GameObjectsList.begin() + i);
			i--;
		}
	}
	
	//putting the background for the stars here
	background.Update(dt);
}

void Game::Draw(sf::RenderWindow & window)
{
	//draw the stars BEFORE the game objects
	//this keeps them behind the walls and everything else
	background.Draw(window);
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
void Game::ObjectQuickSort(int left, int right)
{
	//outer indices of the list of objects
	// needed for the recursive call
	// need these temps iter values to also have initual values left and right
	int i = left;
	int j = right;

	int index = (left + (right - left)) / 2;
	float pivot = m_GameObjectsList[index]->GetBody().getPosition().x;
	
	// partition
	//as long as i is less than j
	// then left is still left of right, right?
	// find the ones out of place and move that bitch

	while (i < j)
	{
		while (m_GameObjectsList[i]->GetBody().getPosition().x < pivot)
		{
			i++;
		}
		while (m_GameObjectsList[j]->GetBody().getPosition().x > pivot)
		{
			j--;
		}

		//switch around ones found to be in the wrong place
		if (m_GameObjectsList[i]->GetBody().getPosition().x >= 
			m_GameObjectsList[j]->GetBody().getPosition().x)
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

bool Game::MySortFunc(GameObject * i, GameObject * j)
{
	bool _temp = (i->GetBody().getPosition().x) < (j->GetBody().getPosition().x);
	return (i->GetBody().getPosition().x) < (j->GetBody().getPosition().x);
}
