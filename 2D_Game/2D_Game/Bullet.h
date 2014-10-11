#pragma once

#include "SFML\Graphics.hpp"

class Bullet
{
public:
	int x;
	int y;
	int damage;
	int range;
	int speed;
	sf::Texture texture;

public:
	Bullet(void);
	~Bullet(void);
};

