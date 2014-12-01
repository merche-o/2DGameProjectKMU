#pragma once

#include "SFML\Graphics.hpp"

class Item
{


public:
	enum itemType 
{
	COINS,
	AMMO,
	D_WEAPON
};
	float x;
	float y;
	float spawnTime;
	float lifeTime;
	float loopTime;
	float timeSpawn;
	sf::Texture texture;
	itemType type;
	int score;
public:
	Item(float X, float Y,  float LifeTime, sf::Texture Texture, itemType type, int score);
	Item(Item const &);
	Item();
	~Item(void);
};

