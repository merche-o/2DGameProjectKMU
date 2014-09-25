#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: graphic(window, map, player), map(), event(window, player)
{
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);

	player.push_back(new Player());
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::run()
{
    while (window.isOpen())
    {
		window.clear();

		graphic.affMap();
		graphic.affPlayer();

		event.checkEvent();
		
		graphic.RefreshWindow();
    }
}