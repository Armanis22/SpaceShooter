// SFMLTemplate.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>

#include "Game.h"


int main()
{
	Game game;
	sf::RenderWindow window(sf::VideoMode(1200, 720), "Pew Pew Pew!");
	window.setMouseCursorVisible(false);

	while (!game.Quitting())
	{
		game.Play(window);
	}

	return 0;
}

