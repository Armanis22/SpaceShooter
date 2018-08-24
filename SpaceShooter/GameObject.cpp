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
	m_Body.setSize({ 40,20 });
	m_Body.setPosition({ 100, 300 });
	m_Body.setOrigin({ m_Body.getSize().x / 2,m_Body.getSize().y / 2 });
	printf("Called\n");

}