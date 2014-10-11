#pragma once

#include "Bullet.h"

class Weapon
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

