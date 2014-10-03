#include "Platform.h"


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