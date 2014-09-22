#pragma once

#include "SFML\Graphics.hpp"

class Bullet
{
private:
	int x;
	int y;
	int damage;
	int range;
	int speed;
	sf::Image image;

public:
	Bullet(void);
	~Bullet(void);
};

