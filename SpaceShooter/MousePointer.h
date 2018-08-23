#pragma once
#include "SFML\Graphics.hpp"

class MousePointer
{


private:
	sf::CircleShape innerTarget;
	sf::CircleShape outerTarget;

public:
	MousePointer()
	{
		innerTarget.setFillColor(sf::Color::Red);
		innerTarget.setRadius(2);
		innerTarget.setOrigin(2, 2);
		
		outerTarget.setFillColor(sf::Color::Transparent);
		outerTarget.setRadius(15);
		outerTarget.setOrigin(15,15);
		outerTarget.setOutlineColor(sf::Color::Red);
		outerTarget.setOutlineThickness(2);

		
	};

	void Update(sf::Vector2i mousePos)
	{
		float posX(static_cast<float>(mousePos.x));
		float posY(static_cast<float>(mousePos.y));
		sf::Vector2f pos(posX,posY);
		innerTarget.setPosition(pos);
		outerTarget.setPosition(pos);
	};

	sf::CircleShape InnerTarget() { return innerTarget; }
	sf::CircleShape OuterTarget() { return outerTarget; }

	~MousePointer() {};
};
