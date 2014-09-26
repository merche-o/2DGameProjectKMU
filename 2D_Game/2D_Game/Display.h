#pragma once

#include "SFML\Graphics.hpp"
#include "Player.h"

class Display
{
private:
	sf::RenderWindow & win;

public:
	Display(sf::RenderWindow &);
	~Display(void);

	void loadImage(float x, float y, sf::Texture & texture);
	void loadUnit(float x, float y, AUnit* unit);
	void loadText(float, float, sf::Font, std::string, int size, int r, int g, int b);
	void RefreshWindow();
};

