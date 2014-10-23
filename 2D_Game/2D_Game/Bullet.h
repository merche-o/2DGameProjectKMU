#pragma once

#include "SFML\Graphics.hpp"

class Bullet
{
public:
	enum e_type
	{
		NORMAL,
		SPEEDING
	};

public:
	float x;
	float y;
	int damage;
	float range;
	float speedX;
	float speedY;
	float const &loopTime;
	e_type type;
	sf::Texture texture;

public:
	Bullet(float X, float Y, int Damage, float Range, float SpeedX, float SpeedY, float  &LoopTime);
	~Bullet(void);
	bool destroy();
};

