#include "Bullet.h"


Bullet::Bullet(float X, float Y, int Damage, float Range, int DirX, int DirY, float Speed, float &LoopTime, int NumPlayer): 
x(X), y(Y), damage(Damage), range(Range), dirX(DirX), dirY(DirY), speed(Speed * Settings::CASE_SIZE),loopTime(LoopTime), numPlayer(NumPlayer)
{
	type = NORMAL;
	texture.loadFromFile("./Ressources/Images/bullet1.png");
	pX = x;
	pY = y;
	prevX = x;
	prevY = y;
}

bool Bullet::destroy()
{
	if ( (x - pX) / Settings::CASE_SIZE  >= range  || (y - pY) / Settings::CASE_SIZE <= -range || (x- pX) / Settings::CASE_SIZE  <= -range)
		return true;
	return false;
}


Bullet::~Bullet(void)
{
}

