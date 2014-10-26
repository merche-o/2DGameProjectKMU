#pragma once

#include "SFML\Graphics.hpp"

class Item
{
public:
	float x;
	float y;
	float spawnTime;
	float lifeTime;

public:
	Item(void);
	~Item(void);
};

