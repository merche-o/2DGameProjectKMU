#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: ressources(), graphic(window, map, player, ennemyList, bulletList, ressources, loopTime), menu(window, event, parameters, restart), sound(), map(loopTime), event(window, player), ref(ennemyList, itemList, bulletList, map, loopTime), physics(player, ennemyList, itemList, bulletList, map, loopTime), spawner(ennemyList, itemList, loopTime), IA(ref, ennemyList) 
{
	ressources.loadEnnemiesFromFile("../Ressources/Ennemies.txt");
	ressources.loadWeaponsFromFile("../Ressources/Weapons.txt");
	sound.musicOFF();
	sound.playMusic(sound.music);


	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	
	player.push_back(new Player(ressources, loopTime));
	
	state = MENU;
	restart = false;
}


GameEngine::~GameEngine(void)
{
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
				ennemyList.clear();
				bulletList.clear();
				itemList.clear();
				player.clear();
				player.push_back(new Player(ressources, loopTime));
				globalClock.restart();
				restart = false;
			}
			
			window.clear();
	
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();

			if (ref.dealDamage(player) == false)
				state = MENU;
			ref.cleanEnemyList();
			ref.moveBullet();
			spawner.spawnEnnemies(ressources.ennemy);
			physics.playerAction(0);
			IA.setEnnemiesIM();
			physics.enemyAction();
			map.checkPlatform();

			graphic.affInterface();
			graphic.affMap();
			graphic.affUnits();
			graphic.affBullets();

			if (state == GAME)
				event.checkEvent();
		
		
			graphic.RefreshWindow();
		}
    }
}