#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: graphic(window, map), map(), event(window)
{
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);
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

		event.checkEvent();
		
		graphic.RefreshWindow();
    }
}