#pragma once

#include <list>
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
	std::list<AUnit*> ennemyList;
	std::list<Item*> itemList;
	Map map;
	Player player[2];
	std::list<Bullet*> bulletList;
	Spawner spawner;

public:
	sf::RenderWindow window;
	Event event;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
};

