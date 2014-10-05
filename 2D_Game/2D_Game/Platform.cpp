#include "Platform.h"
#include <iostream>

Platform::Platform(int X, int Y, int Length)
	: x(X), y(Y), length(Length)
{
	for (int i = x; i < x + length; ++i)
	{
		pos.push_back(std::make_pair(i, y));
	}

	type = DISAPPEAR;
	isMorphing = false;
	morphTime = 5;
	transp = 255;
	timer.restart();
}


Platform::~Platform(void)
{
}

void Platform::checkMorphTime()
{
	morph = timer.getElapsedTime();
	if (isMorphing == false && morph.asSeconds() > morphTime) 
	{
		isMorphing = true;
	}
}

void Platform::playMorph()
{
	if (type == DISAPPEAR)
		transp -= 5;
}

bool Platform::checkDead()
{
	if (type == DISAPPEAR && transp == 0)
		return (true);
	return (false);
}