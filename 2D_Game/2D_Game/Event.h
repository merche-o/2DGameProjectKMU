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
		I_SWAP,
		I_WEAPON_1,
		I_WEAPON_2,
		I_WEAPON_3,
		I_WEAPON_4,
		I_NONE,
	};

	enum focus_state
	{
		NONE,
		LOST,
		GAINED,
		CHANGING_TO_DESKTOP_RESOLUTION
	};

	std::vector<Player*> & player;

private:
	sf::Window & win;
	sf::Event event;
public:
	bool &keySettings;
	bool quitPause;
	Event(sf::Window & w, std::vector<Player*> & p, bool &keySettings);
	~Event(void);


	void alternateEventPressed(bool &pause);
	void alternateEventReleased(bool &pause);
	void checkEvent(bool & pause, focus_state &);
	void menuEvent(int & pos, bool & push, bool & refresh, focus_state & focus, bool main, bool pause = false);
};

