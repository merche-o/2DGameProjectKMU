#include "Bullet.h"


Bullet::Bullet(float X, float Y, int Damage, float Range, float Speed)
{
	type = NORMAL;
	texture.loadFromFile("../Ressources/Images/bullet1");
}


Bullet::~Bullet(void)
{
}
