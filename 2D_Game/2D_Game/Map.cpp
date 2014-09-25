#include "Map.h"
#include "Settings.h"

Map::Map(void)
{
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	for (int y = 0; y < height_map; ++y)
	{
		for (int x = 0; x < width_map; ++x)
		{
			if (y == height_map - 1)
				map[std::make_pair(y, x)].type = WALL;
			else
				map[std::make_pair(y, x)].type = NONE;
		}
	}
}


Map::~Map(void)
{
}

