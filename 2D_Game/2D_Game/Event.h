#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Player.h"

class Event
{
public:
	enum Input
	{
		I_UP,
		I_DOWN,
		I_LEFT,
		I_RIGHT,
		I_FIRE_UP,
		I_FIRE_DOWN,
		I_FIRE_LEFT,
		I_FIRE_RIGHT,
		I_BONUS,
		I_NONE
	};

private:
	sf::Window & win;
	sf::Event event;
	std::vector<Player*> & player;

public:
	Event(sf::Window & w, std::vector<Player*> & p);
	~Event(void);

	void checkEvent(bool & pause);
	void menuEvent(int & pos, bool & push, bool & refresh, bool pause = false);
};

