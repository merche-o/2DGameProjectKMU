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

void Graphic::affInterface()
{
	sf::Texture texture;
	texture.loadFromFile("../Ressources/Images/Interface.png");
	loadImage(0, 0, texture);

	sf::Font font;
	font.loadFromFile("../Ressources/Text/Pixel.ttf");
	loadText(1 * Settings::CASE_SIZE, 8, font, std::string("Player1"), 32, 250, 250, 60);

	texture.loadFromFile("../Ressources/Images/LifeBar.png");
	for (int j = 0; j < player[0]->life; ++j)
	{
		loadImage(4 * Settings::CASE_SIZE + (j * texture.getSize().x), 0.8 * Settings::CASE_SIZE, texture);
	}

	texture.loadFromFile("../Ressources/Images/ShieldBar.png");
	for (int k = player[0]->life; k < player[0]->life + player[0]->shield; ++k)
	{
		loadImage(4 * Settings::CASE_SIZE + (k * texture.getSize().x), 0.8 * Settings::CASE_SIZE, texture);
	}
}

void Graphic::affMap()
{
	int height_map = (Settings::HEIGHT + Settings::HEIGHT_INTERFACE) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	sf::Texture texture;
	texture.loadFromFile("../Ressources/Images/Wall.png");

	for (int i = 0; i < map.platform.size(); ++i)
	{
		for (int j = 0; j < (int)map.platform[i]->length; ++j)
		{
			// Display
			if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DISAPPEAR)
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y + Settings::HEIGHT_INTERFACE, texture/*ress.texture["wall"]*/, map.platform[i]->transp);
			else if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DAMAGE)
			{
				sf::Texture texture2;
				texture2.loadFromFile("../Ressources/Images/WallDmg.png");
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y + Settings::HEIGHT_INTERFACE, texture2/*ress.texture["wallDmg"]*/);
			}
			else
				loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y + Settings::HEIGHT_INTERFACE, texture/*ress.texture["wall"]*/);
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