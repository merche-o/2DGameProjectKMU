// Marc

#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: ressources(),
		graphic(window, map, player, ennemyList, bulletList, itemList, ressources, loopTime),
		menu(window, event, parameters, restart, goMenu),
		sound(),
		map(loopTime),
		event(window, player),
		ref(ennemyList, itemList, bulletList, map, loopTime, ressources, sound),
		physics(player, ennemyList, itemList, bulletList, map, loopTime, sound),
		spawner(ennemyList, itemList, loopTime),
		IA(ref, ennemyList) 
{
	ressources.loadEnnemiesFromFile("./Ressources/Ennemies.txt");
	ressources.loadWeaponsFromFile("./Ressources/Weapons.txt");
	sound.musicOFF();
	sound.playMusic(sound.music);

	// Create window
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME, sf::Style::Fullscreen);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	
	player.push_back(new Player(ressources, loopTime, 0));
	
	state = MENU;
	restart = false;
	goMenu = false;
	pause = false;
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::resetElement()
{
	ennemyList.clear();
	bulletList.clear();
	itemList.clear();
	player[0]->init(ressources);
	graphic.resetInterface();
	globalClock.restart();
}

void GameEngine::run()
{
    while (window.isOpen())
    {
		if (state == MENU)
		{
			menu.run();
			
			if (restart == true)
				state = GAME;
		}
		else if (state == GAME)
		{
			if (restart == true)
			{
				resetElement();
				restart = false;
			}
			
			window.clear();
	
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();

			if (ref.dealDamage(player) == false)
			{
					resetElement();
				state = ENDGAME;
				goMenu = false;
				pause = false;
			}
			ref.cleanEnemyList();
			ref.cleanItemList();
			ref.moveBullet(player);
			spawner.spawnEnnemies(ressources.ennemy);
			spawner.spawnAmmo(player[0], ressources.texture["ammo"], &map);
			physics.playerAction(0);
			IA.setEnnemiesIM(player[0]->x, player[0]->y);
			physics.enemyAction();
			map.checkPlatform();
			
			

			graphic.affSpell();
			graphic.affInterface();
			graphic.affMap();
			graphic.affUnits();
			graphic.affBullets();
			graphic.affItems();

			if (state == GAME)
				event.checkEvent(pause);
		
			graphic.RefreshWindow();

			if (pause == true)
			{
				state = PAUSE;
				menu.menuPause();
			}
		}
		else if (state == PAUSE)
		{
			menu.run();
			if (goMenu == true)
			{
				resetElement();
				state = MENU;
				goMenu = false;
				pause = false;
			}
			if (restart == true)
			{
				pause = false;
				state = GAME;
				restart = false;
				globalClock.restart();
			}
		}
    }
}