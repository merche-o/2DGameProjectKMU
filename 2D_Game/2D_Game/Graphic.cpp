#include "Graphic.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, std::vector<AUnit*> & e, std::vector<Bullet*> & b, std::vector<Item*> &i, Ressources & ressource, float & Time)
	: Display(w), win(w), map(m), player(p), ennemyList(e), bulletList(b), itemList(i), ress(ressource), loopTime(Time)
{
	time =0;
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

void Graphic::resetInterface()
	{
		time = 0;
}
void Graphic::affInterface()
{
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
	
	for (int i = 0; i < player.size(); ++i)
	{
		/*** Player n ***/
		loadText(1 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 0, font, std::string("Player" + IntToString(i + 1)), 32, 250, 250, 60);
		// Score
		loadText(4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 0, font, std::string("Score " + IntToString(player[i]->score)), 32, 250, 250, 60);
		// Ammo
		texture.loadFromFile("../Ressources/Images/IAmmo.png");
		loadImage(4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE, texture);
		loadText(5 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE, font, IntToString(player[i]->weapon[0]->ammo), 32, 250, 250, 60);
		// Life
		texture.loadFromFile("../Ressources/Images/LifeBar.png");
		for (int j = 0; j < player[i]->life; ++j)
		{
			loadImage(1 * Settings::CASE_SIZE + (j * texture.getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE, texture);
		}
		// Shield
		texture.loadFromFile("../Ressources/Images/ShieldBar.png");
		for (int k = player[i]->life; k < player[i]->life + player[i]->shield; ++k)
		{
			loadImage(1 * Settings::CASE_SIZE + (k * texture.getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE, texture);
		}
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
	/*** Display Player ***/
	static bool b = true;
	static int t = 0;
	if (player[0]->l_state == HIT)
	{
		++t;
		if (t == 3)
		{
			b = !b;
			t = 0;
		}
		loadHitUnit(player[0], b);
	}
	else
		loadUnit(player[0]);

	/*** Display Enemies ***/
	for (int i = 0; i < ennemyList.size(); ++i)
	{
		loadUnit(ennemyList[i]);
	}
}

void Graphic::affBullets()
{
	for (int i = 0; i < bulletList.size(); ++i)
	{
		loadImage(bulletList[i]->x, bulletList[i]->y + Settings::HEIGHT_INTERFACE, bulletList[i]->texture);
	}
}

void Graphic::affSpell()
{
	if (player[0]->spell.play == true)
	{
		sf::Sprite Sprite;

		Sprite.setTexture(player[0]->spell.texture);
		Sprite.scale(player[0]->spell.scaleX, player[0]->spell.scaleY);
	
		Sprite.setOrigin(16, 16);
		Sprite.setPosition(player[0]->spell.x, player[0]->spell.y);
		loadSprite(Sprite);
	}
}

void Graphic::affItems()
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		loadImage(itemList[i]->x, itemList[i]->y + Settings::HEIGHT_INTERFACE, itemList[i]->texture);
	}
}