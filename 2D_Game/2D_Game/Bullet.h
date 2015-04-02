#pragma once

#include "SFML\Graphics.hpp"
#include "Settings.h"
#include <iostream>


class Bullet
{
public:
	enum e_type
	{
		NORMAL,
		SPEEDING
	};

public:
	int numPlayer;
	float x;
	float y;
	int damage;
	float range;
	int dirX;
	int dirY;
	float speed;
	float const &loopTime;
	e_type type;
	sf::Texture texture;
	float prevX;
	float prevY;
private:
	float pX;
	float pY;
public:
	Bullet(float X, float Y, int Damage, float Range, int dirX, int dirY, float speed,float  &LoopTime, int NumPlayer);
	~Bullet(void);
	bool destroy();
};
