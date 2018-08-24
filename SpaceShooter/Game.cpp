#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	
}


Game::~Game()
{
}

void Game::Play(sf::RenderWindow& window)
{

	

	while (window.isOpen())
	{
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

		//updating the mouse position

		mousePointer.Update(sf::Mouse::getPosition(window));

		window.clear();
		window.draw(mousePointer.InnerTarget());
		window.draw(mousePointer.OuterTarget());

		window.display();
	}

}
