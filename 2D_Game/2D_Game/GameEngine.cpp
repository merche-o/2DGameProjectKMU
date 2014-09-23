#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: window(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), "Ice Cream"),
		event(window)
{
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

		event.checkEvent();
		
        window.display();
    }
}