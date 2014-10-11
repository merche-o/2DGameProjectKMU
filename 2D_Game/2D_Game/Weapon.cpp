#include "Weapon.h"


Weapon::Weapon(int Damage, float FireRate, int Range, int Speed)
	: ammo(0), damage(Damage), fireRate(FireRate), range(Range), speed(Speed)
{
}


Weapon::~Weapon(void)
{
}
