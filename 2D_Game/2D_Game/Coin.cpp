#include "Coin.h"


Coin::Coin(float X, float Y, float LoopTime, int Score, Item::itemType Type, sf::Texture texture): Item(X, Y, 10, texture, Type, Score)
{
	this->timeSpawn = 0;
	this->lifeTime = 10;
}

Coin::Coin(Item const &src)
	: Item(src)
{
}

Coin::~Coin(void)
{
}

