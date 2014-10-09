#include "Graphic.h"
#include "Settings.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, std::vector<AUnit*> & e, Ressources & ressource)
	: Display(w), win(w), map(m), player(p), ennemyList(e), ress(ressource)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::RefreshWindow()
{
	win.display();
}

void Graphic::affMap()
{
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	sf::Texture texture;
	texture.loadFromFile("../Ressources/Images/Wall.png");

	for (int i = 0; i < map.platform.size(); ++i)
	{
		for (int j = 0; j < (int)map.platform[i]->length; ++j)
		{
			// Display
			if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DISAPPEAR)
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y, texture/*ress.texture["wall"]*/, map.platform[i]->transp);
			else if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DAMAGE)
			{
				sf::Texture texture2;
				texture2.loadFromFile("../Ressources/Images/WallDmg.png");
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y, texture2/*ress.texture["wallDmg"]*/);
			}
			else
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y, texture/*ress.texture["wall"]*/);
			//for (int y = 0; y < height_map; ++y)
			//{
			//	for (int x = 0; x < width_map; ++x)
			//	{
			//		if (map[std::make_pair(y, x)].type == WALL)
			//			loadImage(x * (float)Settings::CASE_SIZE, y * (float)Settings::CASE_SIZE, texture/*ress.texture["wall"]*/);
			//	}
			//}
		}
	}
}

void Graphic::affUnits()
{
	loadUnit(player[0]);

	for (int i = 0; i < ennemyList.size(); ++i)
	{
		loadUnit(ennemyList[i]);
	}
}