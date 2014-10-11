#include "Platform.h"
#include "Settings.h"
#include <iostream>
#include <cstdlib>

Platform::Platform(int X, int Y, int Length)
	: x(X), y(Y), length(Length)
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
	activMorph = 200;
	morphTime = 2;
	transp = 255;
	timer.restart();
}


Platform::~Platform(void)
{
}

void Platform::checkMorphTime()
{
	morph = timer.getElapsedTime();
	if (isMorphing == false && morph.asSeconds() > activMorph)
		isMorphing = true;
}

void Platform::playMorph(std::vector<Platform*> & platform)
{
	if (type == DISAPPEAR)
	{
		morph = timer.getElapsedTime();
		transp = (morphTime - (morph.asSeconds() - activMorph)) * 255 / morphTime;
		if (transp < 0)
			transp = 0;
	}
	else if (type == GO_LEFT)
		--x;
	else if (type == GO_RIGHT)
		++x;
	else if (type == DAMAGE)
	{
		// check morphTime
		morph = timer.getElapsedTime();
		if ((morph.asSeconds() -  activMorph) >= morphTime)
		{
			type = DISAPPEAR;
			timer.restart();
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