#pragma once

#include "SFML\Graphics.hpp"

class ImageMenu
{
public:
	float x;
	float y;
	sf::Texture & texture;

public:
	ImageMenu(float X, float Y, sf::Texture & t);
	~ImageMenu(void);
};

