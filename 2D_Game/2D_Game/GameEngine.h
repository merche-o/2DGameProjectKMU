#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "PhysicEngine.h"
#include "Referee.h"
#include "Settings.h"
#include "Parameters.h"
#include "Graphic.h"
#include "GameMenu.h"
#include "Player.h"
#include "Item.h"
#include "Event.h"
#include "Map.h"
#include "Spawner.h"
#include "SoundEngine.h"
#include "Ressources.h"
#include "IA.h"

enum e_state
{
	MENU,
	GAME,
	PAUSE
};

class GameEngine
{
private:
	e_state state;
	Ressources ressources;
	Parameters parameters;
	Graphic graphic;
	GameMenu menu;
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
	bool restart;
	bool goMenu;
	bool pause;
	
	sf::Clock globalClock;
	sf::Time globalTimer;
	float loopTime;

public:
	sf::RenderWindow window;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
};

