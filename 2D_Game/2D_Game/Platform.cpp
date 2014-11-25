#include "Platform.h"
#include "Settings.h"
#include <iostream>
#include <cstdlib>

Platform::Platform(int X, int Y, int Length, float & Time)
	: x(X), y(Y), length(Length), loopTime(Time)
{
	for (int i = 0; i < length; ++i)
	{
		pos.push_back(std::make_pair((i * Settings::CASE_SIZE) + x, y));
	}

	srand(x + y + length);
	int r = rand() % 4;
	if (r == 0)
		type = DISAPPEAR;
	else if (r == 1)
		type = GO_LEFT;
	else if (r == 2)
		type = GO_RIGHT;
	else if (r == 3)
		type = DAMAGE;

	isMorphing = false;
	activMorph = 20;
	morphTime = 2;
	transp = 255;
	speed = 1 * Settings::CASE_SIZE;
}


Platform::~Platform(void)
{
}

void Platform::checkMorphTime()
{
	if (isMorphing == false && morph > activMorph)
		isMorphing = true;
}

void Platform::playMorph(std::vector<Platform*> & platform)
{
	if (type == DISAPPEAR)
	{
		transp = (morphTime - (morph - activMorph)) * 255 / morphTime;
		if (transp < 0)
			transp = 0;
	}
	else if (type == GO_LEFT)
		x -= speed * loopTime;
	else if (type == GO_RIGHT)
		x += speed * loopTime;
	else if (type == DAMAGE)
	{
		if ((morph -  activMorph) >= morphTime)
		{
			type = DISAPPEAR;
			resetTime();
			isMorphing = false;
		}
	}
}

bool Platform::checkDead()
{
	if (type == DISAPPEAR && transp <= 0)
		return (true);
	else if (type == GO_LEFT && (x + Settings::CASE_SIZE * length) <= 0)
		return (true);
	else if (type == GO_RIGHT && x >= Settings::WIDTH)
		return (true);
	return (false);
}

void Platform::refreshTime()
{
	morph += loopTime;
}

void Platform::resetTime()
{
	morph = 0;
}