#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "PhysicEngine.h"
#include "Referee.h"
#include "Settings.h"
#include "Graphic.h"
#include "Player.h"
#include "Item.h"
#include "Event.h"
#include "Map.h"
#include "Spawner.h"
#include "SoundEngine.h"
#include "Ressources.h"
#include "IA.h"

enum gameState {
IN_GAME,
MENU,
END_GAME,
PAUSE
};

class GameEngine
{
private:
	Ressources ressources;
	Graphic graphic;
	SoundEngine sound;
	PhysicEngine physics;
	Referee ref;
	std::vector<AUnit*> ennemyList;
	std::vector<Item*> itemList;
	Map map;
	std::vector<Player*> player;
	std::vector<Bullet*> bulletList;
	Spawner spawner;
	Event event;
	IA IA;
	
	sf::Clock globalClock;
	sf::Time globalTimer;
	float loopTime;

	gameState game;

public:
	sf::RenderWindow window;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
};

