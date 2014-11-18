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
	int numPlayer;
	float fireRateCount;

public:
	Weapon(int Damage, float FireRate, int Range, int Speed, int NumPlayer);
	Weapon(int Damage, float FireRate, int Range, int Speed);
	~Weapon(void);
	Bullet *createBullet(float x, float y, int dirX, int dirY, float &LoopTime);
};

