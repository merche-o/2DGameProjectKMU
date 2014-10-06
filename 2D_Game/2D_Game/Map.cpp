#include "Map.h"
#include "Settings.h"

Map::Map(void)
{
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	//for (int y = 0; y < height_map; ++y)
	//{
	//	for (int x = 0; x < width_map; ++x)
	//	{
	//		map[std::make_pair(y, x)].type = NONE;
	//	}
	//}
	createPlatform(1, height_map - 1, width_map - 2);
	createPlatform(0, height_map - 5, 10, true);
	createPlatform(14, height_map - 5, 4, true);
	createPlatform(7, height_map - 9, 8, true);
	createPlatform(10, height_map - 13, 4, true);
	createPlatform(18, height_map - 13, 4);
	createPlatform(13, height_map - 17, 6, true);
	createPlatform(2, height_map - 12, 4, true);
	createPlatform(1, height_map - 16, 1, true);
	createPlatform(7, height_map - 17, 2, true);
	createPlatform(0, height_map - 17, 1, true);
	createPlatform(10, height_map - 21, 10, true);
	createPlatform(2, height_map - 21, 4, true);
	createPlatform(1, height_map - 25, width_map - 2);
}


Map::~Map(void)
{
}

void Map::createPlatform(int x, int y, int length, bool symmetry)
{
	platform.push_back(new Platform(x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length));
	
	//for (int i = x; i < x + length; ++i)
	//{
	//	map[std::make_pair(y, i)].type = WALL;
	//}

	if (symmetry == true)
	{
		int width_map = Settings::WIDTH / Settings::CASE_SIZE;
		int new_x = width_map - (x + length);

		platform.push_back(new Platform(new_x * Settings::CASE_SIZE, y * Settings::CASE_SIZE, length));

		//for (int i = new_x; i < new_length; ++i)
		//{
		//	map[std::make_pair(y, i)].type = WALL;
		//}
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
				platform[i]->playMorph();
		}
	}
}