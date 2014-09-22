#pragma once

#include "SFML\Graphics.hpp"

class Item
{
private:
	int x;
	int y;
	sf::Clock spawn;
	sf::Clock timer;
	sf::Clock lifeTime;

public:
	Item(void);
	~Item(void);
};

