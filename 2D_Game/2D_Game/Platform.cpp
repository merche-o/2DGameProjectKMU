#include "Platform.h"
#include "Settings.h"

Platform::Platform(int X, int Y, int Length)
	: x(X), y(Y), length(Length)
{
	for (int i = 0; i < length; ++i)
	{
		pos.push_back(std::make_pair(i + x / Settings::CASE_SIZE, y / Settings::CASE_SIZE));
	}

	type = DISAPPEAR;
	isMorphing = false;
	activMorph = 5;
	morphTime = 1;
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

void Platform::playMorph()
{
	if (type == DISAPPEAR)
	{
		morph = timer.getElapsedTime();
		transp = ((morphTime) - (morph.asSeconds() - activMorph)) * 255 / morphTime;
		if (transp < 0)
			transp = 0;
	}
}

bool Platform::checkDead()
{
	if (type == DISAPPEAR && transp <= 0)
		return (true);
	return (false);
}