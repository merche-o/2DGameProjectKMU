#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: ressources(), graphic(window, map, player, ennemyList, bulletList, ressources, loopTime), sound(), map(loopTime), event(window, player), ref(ennemyList, itemList, bulletList,map, loopTime), physics(player,ennemyList,itemList, bulletList, map, loopTime), spawner(ennemyList, itemList, loopTime), IA(ref,ennemyList) 
{
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	game = IN_GAME;
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
    while (window.isOpen() && game != END_GAME)
    {
		window.clear();
	
		globalTimer = globalClock.getElapsedTime();
		loopTime = globalTimer.asSeconds();
		globalClock.restart();
		if (ref.dealDamage(player) == false)
			game = END_GAME;
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

		event.checkEvent();
		
		
		graphic.RefreshWindow();
    }
}

//int moveTime(int speed)
//{
//	return ((speed * Settings::CASE_SIZE) * globalTimer);
//}