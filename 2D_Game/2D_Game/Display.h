#pragma once

#include "SFML\Graphics.hpp"

class Display
{
private:
	sf::RenderWindow & win;

public:
	Display(sf::RenderWindow &);
	~Display(void);

	void loadImage(float, float, sf::Texture &);
	void loadText(float, float, sf::Font, std::string, int size, int r, int g, int b);
	void RefreshWindow();
};

