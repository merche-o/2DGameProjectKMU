#pragma once

#include "SFML\Graphics.hpp"

class Item
{


public:
	enum itemType 
{
	COINS,
};
	float x;
	float y;
	float spawnTime;
	float lifeTime;
	float loopTime;
	sf::Texture texture;
	itemType type;
	int score;
public:
	Item(float X, float Y,  float LifeTime, sf::Texture Texture, itemType type, int score);
	Item(Item const &);
	Item();
	~Item(void);
};

