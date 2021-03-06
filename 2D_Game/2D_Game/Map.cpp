#include "Map.h"
#include "Settings.h"
#include <iostream>

Map::Map(Ressources & r, float & Time)
	: ress(r), loopTime(Time)
{
	
}

void Map::init(bool firstTime)
{
	int height_map = (Settings::HEIGHT_GAME + Settings::HEIGHT_INTERFACE) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH_GAME / Settings::CASE_SIZE;

	number_platfoms = 0;

	if (firstTime == false)
	{
		platform.clear();
	}
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
	createPlatform(1, 0, width_map - 2);
}

Map::~Map(void)
{
}

void Map::createPlatform(int x, int y, int length, bool symmetry)
{
	number_platfoms++;

	platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, ress, (unsigned int)(100 * loopTime)));

	if (symmetry == true)
	{
		int width_map = Settings::WIDTH / Settings::CASE_SIZE;
		int new_x = width_map - (x + length);

		platform.push_back(new Platform(new_x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, ress, (unsigned int)(50 * loopTime)));
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
				if (platform[i]->type == platform[i]->DISAPPEAR)
				{
					number_platfoms--;
					platform.erase(platform.begin() + i); // Delete
				}
				else if (platform[i]->type == platform[i]->MAIN)
				{
					if (platform[i]->length > 10)
					{
						// Creer deux platforms separer par un trou central
						platform.push_back(new Platform(platform[i]->x, platform[i]->y, platform[i]->length / 2 - 2, loopTime, ress, platform[i]->length));
						platform.push_back(new Platform(platform[i]->x + ((platform[i]->length / 2) * Settings::CASE_SIZE), platform[i]->y, platform[i]->length / 2 - 2, loopTime, ress, platform[i]->length));
						number_platfoms--;
						platform.erase(platform.begin() + i); // Delete
					}
				}
				else if (isRecyclable(i) == true) // Give another animation
					platform[i]->recycle();
				else
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

		bool isOK = true;
		for (int i = 0; i < platform.size(); ++i)
		{
			if (y * Settings::CASE_SIZE == platform[i]->y)
			{
				if (!(((x * Settings::CASE_SIZE + (length * Settings::CASE_SIZE)) < platform[i]->x)
					|| (x * Settings::CASE_SIZE > (platform[i]->x + platform[i]->length * Settings::CASE_SIZE))))
					isOK = false;
			}
		}
		if (isOK == true)
		{
			platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length, loopTime, ress, (unsigned int)(100 * loopTime), true));
			number_platfoms++;
		}
	}
}