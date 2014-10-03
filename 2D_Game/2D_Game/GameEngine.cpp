#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: ressources(), graphic(window, map, player, ressources), sound(), map(), event(window, player), ref(ennemyList, itemList, map), physics(player,ennemyList,itemList, map)
{
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);

	physics._referee = &ref;

	player.push_back(new Player());
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::run()
{
	//ressources.loadEnnemiesFromFile("../Ressources/Ennemies.txt");
	//sound.playMusic(sound.music);
    while (window.isOpen())
    {
		window.clear();

		graphic.affMap();
		graphic.affPlayer();

		event.checkEvent();
		physics.playerAction(0);
		
		graphic.RefreshWindow();
    }
}