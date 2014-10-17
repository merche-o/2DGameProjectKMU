#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: ressources(), graphic(window, map, player, ennemyList, ressources), sound(), map(loopTime), event(window, player), ref(ennemyList, itemList, map), physics(player,ennemyList,itemList, map), spawner(ennemyList, itemList, loopTime), IA(ref,ennemyList) 
{
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	
	player.push_back(new Player(ressources, loopTime));
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::run()
{
	ressources.loadEnnemiesFromFile("../Ressources/Ennemies.txt");
	ressources.loadWeaponsFromFile("../Ressources/Weapons.txt");
	//sound.playMusic(sound.music);


	globalClock.restart();
    while (window.isOpen())
    {
		window.clear();
	
		globalTimer = globalClock.getElapsedTime();
		loopTime = globalTimer.asSeconds();
		globalClock.restart();
		
		graphic.affInterface();
		map.checkPlatform();
		graphic.affMap();
		spawner.spawnEnnemies(ressources.ennemy);
		graphic.affUnits();

		event.checkEvent();
		physics.playerAction(0);
		IA.setEnnemiesIM();
		physics.enemyAction();
		ref.dealDamage(player);
		ref.cleanEnemyList();
		graphic.RefreshWindow();
    }
}

//int moveTime(int speed)
//{
//	return ((speed * Settings::CASE_SIZE) * globalTimer);
//}