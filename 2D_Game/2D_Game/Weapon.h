#pragma once

#include "Bullet.h"
#include "Item.h"

class Weapon : public Item
{
public:
	int ammo;
	int damage;
	float fireRate;
	int range;
	int speed;
	sf::Texture texture;

public:
	Weapon(int Damage, float FireRate, int Range, int Speed);
	~Weapon(void);
};

