#pragma once

#include <vector>
#include "Display.h"
#include "Map.h"
#include "Player.h"
#include "Ressources.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	Map & map;
	std::vector<Player*> & player;
	Ressources & ress;

public:
	Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, Ressources & ressource);
	~Graphic(void);

	void RefreshWindow();
	void affMap();
	void affPlayer();
};

