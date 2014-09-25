#pragma once

#include "SFML\Graphics.hpp"

class AUnit
{
public:
	int x;
	int y;
	int life;
	int shield;
	int speed;
	sf::Texture texture;
	int animFrame;
	sf::Time spawm;
	sf::Clock timer;

public:
	AUnit(void);
	~AUnit(void);
};