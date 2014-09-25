#pragma once

#include "SFML\Graphics.hpp"

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
	sf::Window & window;
	sf::Event event;

public:
	Event(sf::Window &);
	~Event(void);

	void checkEvent();
};

