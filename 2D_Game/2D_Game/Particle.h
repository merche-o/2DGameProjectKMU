#pragma once

#include "SFML\Graphics.hpp"
#include "Pos.h"

class Particle
{
public:
	float x;
	float y;
	float transp;
	sf::Texture texture;
	sf::Color color;
	float radius;

	std::vector<int> transpGradient;
	std::vector<float> lifeGradient;
	float lifeTime; // Temps de vie max
	float currentTime; // Temps de vie actuel
	float & loopTime;

	Pos speed;

public:
	Particle(float X, float Y, sf::Color, float LifeTime, float SpeedX, float SpeedY, float Radius, float & Time);
	~Particle(void);

	void update();
};

