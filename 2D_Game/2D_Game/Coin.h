#pragma once

#include "Item.h"

class Coin : public Item
{
private:
	int score;

public:
	Coin(void);
	~Coin(void);
};

