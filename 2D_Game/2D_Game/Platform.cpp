// Marc

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

	// Choose a type randomly
	srand(x + y + length);
	int r = rand() % 3;
	if (r == 0)
		type = DISAPPEAR;
	else if (r == 1)
		type = GO_LEFT;
	else if (r == 2)
		type = GO_RIGHT;
	//else if (r == 3)
		//type = DAMAGE;

	r = rand() % 20 + 5;
	isMorphing = false; // not activ
	activMorph = r; // time before active
	morphTime = 3; // time for animation
	transp = 255; // transparency
	speed = 1 * Settings::CASE_SIZE;

	float tmp;
	tmp = morphTime / 6;

	lifeGradient.push_back(morphTime);
	lifeGradient.push_back(tmp * 5);
	lifeGradient.push_back(tmp * 4);
	lifeGradient.push_back(tmp * 3);
	lifeGradient.push_back(tmp * 2);
	lifeGradient.push_back(tmp);

	transpGradient.push_back(0);
	transpGradient.push_back(50);
	transpGradient.push_back(100);
	transpGradient.push_back(150);
	transpGradient.push_back(200);
	transpGradient.push_back(250);
}


Platform::~Platform(void)
{
}

// Check for activation
void Platform::checkMorphTime()
{
	if (isMorphing == false && morph > activMorph)
		isMorphing = true;
}

void Platform::playMorph(std::vector<Platform*> & platform)
{
	if (type == DISAPPEAR)
	{
		for (int i = 0; i < lifeGradient.size(); ++i)
		{
			if (morph >= lifeGradient[i])
			{
				transp = transpGradient[i];
				break;
			}
		}
		/*transp = (morphTime - (morph - activMorph)) * 255 / morphTime;
		if (transp < 0)
			transp = 0;*/
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

// Delete useless platforms
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