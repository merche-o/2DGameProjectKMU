#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Player.h"

class Event
{
	enum Input
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FIRE_UP,
		FIRE_DOWN,
		FIRE_LEFT,
		FIRE_RIGHT,
		BONUS
	};

private:
	sf::Window & win;
	sf::Event event;
	std::vector<Player*> & player;

public:
	Event(sf::Window & w, std::vector<Player*> & p);
	~Event(void);

	void checkEvent();
};

