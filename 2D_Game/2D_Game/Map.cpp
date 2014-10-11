#include "Map.h"
#include "Settings.h"

Map::Map(void)
{
	int height_map = (Settings::HEIGHT_GAME + Settings::HEIGHT_INTERFACE) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH_GAME / Settings::CASE_SIZE;

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

	createPlatform(7, 21, 1);
	createPlatform(width_map - 7, 21, 1);

}


Map::~Map(void)
{
}

void Map::createPlatform(int x, int y, int length, bool symmetry)
{
	platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length));

	if (symmetry == true)
	{
		int width_map = Settings::WIDTH / Settings::CASE_SIZE;
		int new_x = width_map - (x + length);

		platform.push_back(new Platform(new_x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length));
	}
}

void Map::checkPlatform()
{
	for (int i = 0; i < platform.size(); ++i)
	{
		if (platform[i]->isMorphing == false)
			platform[i]->checkMorphTime();

		if (platform[i]->isMorphing == true)
		{
			if (platform[i]->checkDead() == true)
				platform.erase(platform.begin() + i);
			else
				platform[i]->playMorph(platform);
		}
	}
}