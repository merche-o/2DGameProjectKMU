#pragma once

#include "SFML\Graphics.hpp"

class Event
{
private:
	sf::Window & window;
	sf::Event event;

public:
	Event(sf::Window &);
	~Event(void);

	void checkEvent();
};

