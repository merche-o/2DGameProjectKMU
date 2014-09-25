#pragma once

#include "Display.h"
#include "Map.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	Map & map;

public:
	Graphic(sf::RenderWindow &, Map &);
	~Graphic(void);

	void affMap();
};

