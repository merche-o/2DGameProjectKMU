// Marc

#include "Platform.h"
#include "Settings.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Platform::Platform(int X, int Y, int Length, float & Time, Ressources & re, unsigned int randomize, bool rebuild)
	: x(X), y(Y), length(Length), loopTime(Time), ress(re)
{
	// CREATE EACH CASE
	for (int i = 0; i < length; ++i)
	{
		if (i == 0)
			texture.push_back(ress.texture["Lplatform"]);
		else if (i == length - 1)
			texture.push_back(ress.texture["Rplatform"]);
		else
			texture.push_back(ress.texture["Mplatform"]);

		pos.push_back(std::make_pair((i * Settings::CASE_SIZE) + x, y));
	}

	morph = 0;
	
	// Random STATS
	srand(x + y + length + randomize + time(NULL));
	int r = rand() % 3;

	// PLATFORM TYPE ///////////////////////////
	if (rebuild == false) // Platform from beginning
	{
		if (r == 0)
			type = DISAPPEAR;
		else if (r == 1)
			type = GO_LEFT;
		else if (r == 2)
			type = GO_RIGHT;
		//else if (r == 3)
		//	type = GO_UP;
		//else if (type == 4)
		//	type = GO_DOWN;
		//else if (r == 3)
			//type = DAMAGE;
		if (y / Settings::CASE_SIZE == 22)
			type = MAIN;
		else if (y / Settings::CASE_SIZE == 0)
			type = MAIN;
	}
	else if (rebuild == true) // Platform rebuild
		type = APPEARING;
	////////////////////////////////////////////

	// PLATFORM STATS///////////////////////////
	if (rebuild == false) // Platform from beginning
	{
		r = rand() % 15 + 5;
		activMorph = r; // time before active
		transp = 255; // transparency
		if (type == MAIN)
			activMorph = 20;
	}
	else if (rebuild == true) // Platform rebuild
	{
		activMorph = 0;
		transp = 0;
	}

	isMorphing = false; // not activ
	morphTime = 6; // time for animation
	r = rand() % 3 + 1;
	speed = r * Settings::CASE_SIZE;
	////////////////////////////////////////////

	// VECTOR OF TRANSPARENCY //////////////////
	if (type == DISAPPEAR || type == APPEARING)
	{
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

		if (type == APPEARING)
		{
			reverse(transpGradient.begin(), transpGradient.end());
			//reverse(lifeGradient.begin(), lifeGradient.end());
		}
	}
	////////////////////////////////////////////
}


Platform::~Platform(void)
{
}

// Check for activation
void Platform::checkMorphTime()
{
	if (isMorphing == false && morph > activMorph)
	{
		isMorphing = true;
		resetTime();
	}
}

void Platform::playMorph(std::vector<Platform*> & platform) // Creer des collisions de croisement grace a la liste de platform
{
	if (type == GO_RIGHT || type == GO_LEFT)
		isCollidingWithPlatform(platform);
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
		// No more calculation
		/*transp = (morphTime - (morph - activMorph)) * 255 / morphTime;
		if (transp < 0)
			transp = 0;*/
	}
	else if (type == APPEARING)
	{
		for (int i = 0; i < lifeGradient.size(); ++i)
		{
			if (morph >= lifeGradient[i])
			{
				transp = transpGradient[i];
				break;
			}
		}
	}
	else if (type == GO_LEFT)
	{
		x -= speed * loopTime;
	}
	else if (type == GO_RIGHT)
	{
		x += speed * loopTime;
	}
	else if (type == MAIN)
	{
	}
	//else if (type == GO_UP)
	//{
	//	y -= speed * loopTime;
	//}
	//else if (type == GO_DOWN)
	//{
	//	y += speed * loopTime;
	//}


	// No more Damage Platform
	//else if (type == DAMAGE)
	//{
	//	if ((morph -  activMorph) >= morphTime)
	//	{
	//		type = DISAPPEAR;
	//		resetTime();
	//		isMorphing = false;
	//	}
	//}
}

// Delete useless platforms
bool Platform::checkDead()
{
	if (type == DISAPPEAR && transp <= 0)
		return (true);
	else if (type == APPEARING && transp == 255)
		setNewEvent();
	else if (type == GO_LEFT && (x + Settings::CASE_SIZE * length) <= 0)
		return (true);
	else if (type == GO_RIGHT && (x/* + Settings::CASE_SIZE * length*/) >= Settings::WIDTH)
		return (true);
	else if (type == MAIN)
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

void Platform::recycle()
{
	if (type == GO_LEFT)
		type = GO_RIGHT;
	else if (type == GO_RIGHT)
		type = GO_LEFT;
	else if (type == DISAPPEAR)
	{

	}
}

void Platform::setNewEvent()
{
	srand(x + y + length + type + time(NULL));
	
	int r = rand() % 15 + 5;
	activMorph = r; // time before active

	r = rand() % 3;
	if (r == 0)
		type = DISAPPEAR;
	else if (r == 1)
		type = GO_LEFT;
	else if (r == 2)
		type = GO_RIGHT;
}

void Platform::isCollidingWithPlatform(std::vector<Platform*> & platform)
{
	for (int i = 0; i < platform.size(); ++i)
	{
		if (y == platform[i]->y && platform[i] != this)
		{
			if (type == GO_RIGHT)
			{
				// check collision
				if (((x + (length * Settings::CASE_SIZE)) >= (platform[i]->x))
					&& (x < (platform[i]->x + (platform[i]->length * Settings::CASE_SIZE))))
				{
					type = GO_LEFT; // Change de direction

					if (platform[i]->type == GO_LEFT)
						platform[i]->type = GO_RIGHT; // Change de direction
					break;
				}
			}
			else if (type == GO_LEFT)
			{
				// check collision
				if ((x <= (platform[i]->x + (platform[i]->length * Settings::CASE_SIZE)))
					&& ((x + (length * Settings::CASE_SIZE)) > (platform[i]->x)))
				{
					type = GO_RIGHT; // Change de direction

					if (platform[i]->type == GO_RIGHT)
						platform[i]->type = GO_LEFT; // Change de direction
					break;
				}
			}
		}
	}
}