#pragma once

#include "SFML\Graphics.hpp"
#include "Settings.h"
#include "AUnit.h"
#include <iostream>

class Player;

class Bullet
{
public:
	enum e_type
	{
		NORMAL,
		SPEEDING
	};

public:
	AUnit *player;
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
private:
	float pX;
	float pY;
public:
	Bullet(float X, float Y, int Damage, float Range, int dirX, int dirY, float speed,float  &LoopTime, AUnit *Player);
	~Bullet(void);
	bool destroy();
};
