#pragma once

#include "Item.h"

class Ammo : public Item
{
public:
	// Type
	Item::itemType weaponType;

public:
	Ammo(float X, float Y, float lifeTime, float loopTime,sf::Texture texture, Item::itemType iType, Item::itemType wType);
	~Ammo(void);
};

