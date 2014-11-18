#pragma once

#include "Item.h"

class Coin : public Item
{
private:
	int score;

public:
	Coin(float X, float Y, float loopTime, int score, Item::itemType type, sf::Texture Texture);
	Coin(Item const &);
	~Coin(void);
};

