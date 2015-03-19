#pragma once

#include "SFML\Graphics.hpp"

class Particle
{
public:
	float x;
	float y;
	int speed;
	float transp;
	sf::Texture texture;
	sf::Color color;

	float lifeTime;
	float currentTime;
	float & loopTime;

public:
	Particle(float X, float Y, float & Time);
	~Particle(void);

	void update();
};

