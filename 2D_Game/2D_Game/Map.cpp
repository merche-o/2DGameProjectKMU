// Marc

#include "Map.h"
#include "Settings.h"
#include <iostream>

Map::Map(float & Time)
	: loopTime(Time)
{
	
}

void Map::init(bool firstTime)
{
	int height_map = (Settings::HEIGHT_GAME + Settings::HEIGHT_INTERFACE) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH_GAME / Settings::CASE_SIZE;

	number_platfoms = 0;

	if (firstTime == true)
	{
		createPlatform(1, 22, width_map - 2);
		createPlatform(0, 18, 10, true);
		createPlatform(14, 18, 4, true);
		createPlatform(7, 14, 8, true);
		createPlatform(10, 10, 4, true);
		createPlatform(18, 11, 4);
		createPlatform(13, 6, 6, true);
		createPlatform(2, 11, 4, true);
		createPlatform(7, 6, 2, true);
		createPlatform(0, 4, 4, true);
		createPlatform(2, 0, width_map - 4);
	}
	else
	{
		platform.clear();
		
		createPlatform(1, 22, width_map - 2);
		createPlatform(0, 18, 10, true);
		createPlatform(14, 18, 4, true);
		createPlatform(7, 14, 8, true);
		createPlatform(10, 10, 4, true);
		createPlatform(18, 11, 4);
		createPlatform(13, 6, 6, true);
		createPlatform(2, 11, 4, true);
		createPlatform(7, 6, 2, true);
		createPlatform(0, 4, 4, true);
		createPlatform(2, 0, width_map - 4);
	}
}

Map::~Map(void)
{
}

void Map::createPlatform(int x, int y, int length, bool symmetry)
{
	number_platfoms++;

	platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, (unsigned int)(100 * loopTime)));

	if (symmetry == true)
	{
		int width_map = Settings::WIDTH / Settings::CASE_SIZE;
		int new_x = width_map - (x + length);

		platform.push_back(new Platform(new_x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, (unsigned int)(50 * loopTime)));
	}
}

// Run function for platform
void Map::checkPlatform()
{
	rebuildPlatform();
	for (int i = 0; i < platform.size(); ++i)
	{
		platform[i]->refreshTime();

		if (platform[i]->isMorphing == false)
			platform[i]->checkMorphTime();

		if (platform[i]->isMorphing == true)
		{
			if (platform[i]->checkDead() == true) // Is out of animation
			{
				if (isRecyclable(i) == true) // Give another animation
					platform[i]->recycle();
				else
					platform.erase(platform.begin() + i); // Delete

				if (platform[i]->type == platform[i]->DISAPPEAR)
				{
					number_platfoms--;
					platform.erase(platform.begin() + i); // Delete
				}
			}
			else
				platform[i]->playMorph(platform);
		}
	}
}

bool Map::isRecyclable(int n)
{
	for (int i = 0; i < platform.size(); ++i)
	{
		if (i != n)
		{
			if (platform[n]->y == platform[i]->y)
				return (false);
		}
	}
	return (true);
}

void Map::rebuildPlatform()
{
	if (number_platfoms < 10) // Minimum platforms in the Map
	{
		srand(time(NULL) * number_platfoms);
		int length = rand() % 8 + 2; // Valeur length de 2 a 10
		int y = rand() % 18 + 3; // Vertical position
		int x = rand() % 40; // Horizontal position
		if (x + length > 40)
			x += 39 - x - length; // Recalage droite
		else if (x < 0)
			x = 0; // Recalage gauche

		platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, (unsigned int)(100 * loopTime), true));
		//platform[platform.size() - 1]->type = Platform::APPEARING;
		number_platfoms++;
	}
}