#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Settings.h"
#include "Graphic.h"
#include "Player.h"
#include "Item.h"
#include "Event.h"
#include "Map.h"
#include "Spawner.h"

class GameEngine
{
private:
	Graphic graphic;
	std::vector<AUnit*> ennemyList;
	std::vector<Item*> itemList;
	Map map;
	std::vector<Player*> player;
	std::vector<Bullet*> bulletList;
	Spawner spawner;
	Event event;

public:
	sf::RenderWindow window;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
};

