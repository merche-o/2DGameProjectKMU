#pragma once

#include "SFML\Graphics.hpp"

enum e_type
{
	UP,
	DOWN,
	DISPERSE,
	NONE
};

class Particle
{
public:
	float x;
	float y;
	int speed;
	float transp;
	sf::Texture texture;
	sf::Color color;
	e_type type;

	float lifeTime;
	float currentTime;
	float & loopTime;

public:
	Particle(float X, float Y, sf::Color, float LifeTime, int Speed, e_type Type, float & Time);
	~Particle(void);

	void update();
};

