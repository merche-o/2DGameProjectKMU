#include "Graphic.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, std::vector<AUnit*> & e, std::vector<Bullet*> & b, Ressources & ressource, float & Time)
	: Display(w), win(w), map(m), player(p), ennemyList(e), bulletList(b), ress(ressource), loopTime(Time)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::RefreshWindow()
{
	win.display();
}

std::string testDecade(int n)
{
	if (n < 10)
		return (std::string("0"));
	return ("");
}

void Graphic::affInterface()
{
	sf::Font font;
	font.loadFromFile("../Ressources/Text/Text.ttf");

	/*** Fond Interface ***/
	sf::Texture texture;
	texture.loadFromFile("../Ressources/Images/Interface.png");
	loadImage(0, 0, texture);

	/*** Chrono ***/
	time += loopTime;
	float t = floor(time);
	int min = (int)t / 60;
	int sec = (int)t % 60;
	loadText(18 * Settings::CASE_SIZE, 0, font, std::string(testDecade(min) + IntToString(min) + ":" + testDecade(sec) + IntToString(sec)), 32, 250, 180, 60);
	
	/*** Player 1 ***/
	loadText(1 * Settings::CASE_SIZE, 0, font, std::string("Player1"), 32, 250, 250, 60);
	// Score
	loadText(4 * Settings::CASE_SIZE, 0, font, std::string(IntToString(player[0]->score)), 32, 250, 250, 60);
	// Life
	texture.loadFromFile("../Ressources/Images/LifeBar.png");
	for (int j = 0; j < player[0]->life; ++j)
	{
		loadImage(1 * Settings::CASE_SIZE + (j * texture.getSize().x), 1 * Settings::CASE_SIZE, texture);
	}
	// Shield
	texture.loadFromFile("../Ressources/Images/ShieldBar.png");
	for (int k = player[0]->life; k < player[0]->life + player[0]->shield; ++k)
	{
		loadImage(1 * Settings::CASE_SIZE + (k * texture.getSize().x), 1 * Settings::CASE_SIZE, texture);
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
	static bool b = true;
	static int t = 0;
	// if player[0]->l_state == HIT
	// faire clignoter le joueur pendant 2 sec, puis le remettre en l_state = IN_LIFE
	if (player[0]->l_state == HIT)
	{
		++t;
		if (t == 4)
		{
			b = !b;
			t = 0;
		}
		loadHitUnit(player[0], b);
	}
	else
		loadUnit(player[0]);

	for (int i = 0; i < ennemyList.size(); ++i)
	{
		loadUnit(ennemyList[i]);
	}
}

void Graphic::affBullets()
{
	for (int i = 0; i < bulletList.size(); ++i)
	{
		loadImage(bulletList[i]->x, bulletList[i]->y, bulletList[i]->texture);
	}
}