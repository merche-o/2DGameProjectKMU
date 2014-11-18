#include "Weapon.h"


Weapon::Weapon(int Damage, float FireRate, int Range, int Speed, int NumPlayer)
	: ammo(10), damage(Damage), fireRate(FireRate), range(Range), speed(Speed), numPlayer(NumPlayer)
{
	fireRateCount = fireRate;
}

Weapon::Weapon(int Damage, float FireRate, int Range, int Speed)
	: ammo(10), damage(Damage), fireRate(FireRate), range(Range), speed(Speed)
{
}



Weapon::~Weapon(void)
{
}

Bullet *Weapon::createBullet(float x, float y, int dirX, int dirY, float &LoopTime)
{
	if (ammo > 0)
		{
			ammo--;
			return new Bullet(x, y, damage,range, dirX, dirY, speed, LoopTime, numPlayer);
		}
		return NULL;
}
