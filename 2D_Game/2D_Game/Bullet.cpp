#include "Bullet.h"


Bullet::Bullet(float X, float Y, int Damage, float Range, float SpeedX, float SpeedY, float &LoopTime): x(X), y(Y), damage(Damage), range(Range), speedX(SpeedX), speedY(SpeedY), loopTime(LoopTime)
{
	type = NORMAL;
	texture.loadFromFile("../Ressources/Images/bullet1.png");
}

bool Bullet::destroy()
{
	if (range <= 0)
		return true;
	range -= loopTime;
	return false;
}


Bullet::~Bullet(void)
{
}

