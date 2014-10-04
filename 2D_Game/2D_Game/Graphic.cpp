#include "Graphic.h"
#include "Settings.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, Ressources & ressource)
	: Display(w), win(w), map(m), player(p), ress(ressource)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::affMap()
{
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	sf::Texture texture;
	texture.loadFromFile("../Ressources/Images/Wall.png");

	for (int i = 0; i < map.platform.size(); ++i)
	{
		for (int x = 0; x < map.platform[i]->length; ++x)
		{
			//if (map.platform[i]->isMorphing == false)
			//	map.platform[i]->checkMorphTime();
			//if (map.platform[i]->isMorphing == true)
			//{
			//	if (map.platform[i]->checkDead() == true)
			//	{
			//		map.platform.erase(map.platform.begin() + i);
			//		break;
			//	}
			//	map.platform[i]->playMorph();
			//}

			// Display
			loadImage(map.platform[i]->pos[x].first * (float)Settings::CASE_SIZE, map.platform[i]->pos[x].second * (float)Settings::CASE_SIZE, texture/*ress.texture["wall"]*/);
			//if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DISAPPEAR)
			//	loadImage(map.platform[i]->pos[x].first * (float)Settings::CASE_SIZE, map.platform[i]->pos[x].second * (float)Settings::CASE_SIZE, texture/*ress.texture["wall"]*/, map.platform[i]->transp);
		}
	}

	//for (int y = 0; y < height_map; ++y)
	//{
	//	for (int x = 0; x < width_map; ++x)
	//	{
	//		if (map.map[std::make_pair(y, x)].type == WALL)
	//			loadImage(x * (float)Settings::CASE_SIZE, y * (float)Settings::CASE_SIZE, texture/*ress.texture["wall"]*/);
	//	}
	//}
}

void Graphic::affPlayer()
{
	loadUnit((float)player[0]->x, (float)player[0]->y, player[0]);
}