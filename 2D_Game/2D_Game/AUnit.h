#pragma once

#include "SFML\Graphics.hpp"

class AUnit
{
private:
	int x;
	int y;
	int life;
	int shield;
	int speed;
	sf::Image image;
	int animFrame;
	sf::Clock spawm;
	sf::Clock timer;

public:
	AUnit(void);
	~AUnit(void);
};