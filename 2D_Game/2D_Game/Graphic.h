#pragma once

#include <vector>
#include "Display.h"
#include "Map.h"
#include "Player.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	Map & map;
	std::vector<Player*> & player;

public:
	Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p);
	~Graphic(void);

	void affMap();
	void affPlayer();
};

