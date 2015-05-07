#pragma once

#include "SFML\Graphics.hpp"
#include "Player.h"

class Display
{
private:
	sf::RenderWindow & win;

public:
	sf::Font font;

public:
	Display(sf::RenderWindow &);
	~Display(void);

	void loadParticleVector(std::vector<Particle*> & particles);
	void loadCircle(float x, float y, float radius, sf::Color color, int transparency);
	void loadImage(float x, float y, sf::Texture & texture, int transparency = 255);
	void loadSprite(sf::Sprite Sprite);
	void loadUnit(AUnit* unit);
	void loadHitUnit(AUnit* unit, bool b);
	void loadText(float, float, sf::Font, std::string, int size, int r, int g, int b);
	void RefreshWindow();
};

