#include "Bullet.h"


Bullet::Bullet(float X, float Y, int Damage, float Range, float SpeedX, float SpeedY): x(X), y(Y), damage(Damage), range(Range), speedX(SpeedX), speedY(SpeedY)
{
	type = NORMAL;
	texture.loadFromFile("../Ressources/Images/bullet1.png");
}


Bullet::~Bullet(void)
{
}
