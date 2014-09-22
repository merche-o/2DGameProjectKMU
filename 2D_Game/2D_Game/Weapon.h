#pragma once

#include "Bullet.h"

class Weapon
{
private:
	int ammo;
	int damage;
	int fireRate;
	int range;
	int speed;
	sf::Image image;

public:
	Weapon(void);
	~Weapon(void);
};

