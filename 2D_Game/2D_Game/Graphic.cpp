//Marc

#include "Graphic.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, std::vector<AUnit*> & e, std::vector<Bullet*> & b, std::vector<Item*> &i, Ressources & ressource, float & Time)
	: Display(w), win(w), map(m), player(p), ennemyList(e), bulletList(b), itemList(i), ress(ressource), loopTime(Time)
{
	time = 0;
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
	loadImage(0, 0 + Settings::HEIGHT_GAME, ress.texture["interface"]);

	/*** Chrono ***/
	time += loopTime;
	float t = floor(time);
	int min = (int)t / 60;
	int sec = (int)t % 60;
	loadText(Settings::CASE_SIZE, 13 + Settings::HEIGHT_GAME, font, std::string(testDecade(min) + IntToString(min) + ":" + testDecade(sec) + IntToString(sec)), 32, 250, 180, 60);
	
	for (int i = 0; i < player.size(); ++i)
	{
		/*** Player n ***/
		loadText(18 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Life"), 16, 250, 250, 60);
		// Life
		for (int j = 0; j < player[i]->life; ++j)
		{
			loadImage(17.5 * Settings::CASE_SIZE + (j * ress.texture["life"].getSize().x + 7 * j) + (i * (20 * Settings::CASE_SIZE)), 0.9 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, ress.texture["life"]);
		}
		// Shield
		for (int k = player[i]->life; k < player[i]->life + player[i]->shield; ++k)
		{
			loadImage( 17.5 * Settings::CASE_SIZE + (k * ress.texture["shield"].getSize().x + 7 * k) + (i * (20 * Settings::CASE_SIZE)), 0.9 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, ress.texture["shield"]);
		}
		// Ammo
		if (player[i]->weaponUsed == 0)
		loadImage(8 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["weaponUsed"]);
		else if (player[i]->weaponUsed == 1)
			loadImage(9.7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["weaponUsed"]);
		else if (player[i]->weaponUsed == 2)
			loadImage(11.4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["weaponUsed"]);
		loadText(9 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Weapons"), 16, 250, 250, 60);
		loadImage(8 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["ammoLogo"]);
		loadText(8.7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME, font, IntToString(player[i]->weapon[0]->ammo), 10, 250, 250, 60);
		loadImage(9.7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["ammoLogo1"]);
		loadText(10.4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME, font, IntToString(player[i]->weapon[1]->ammo), 10, 250, 250, 60);
		loadImage(11.4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["ammoLogo2"]);
		loadText(12.1 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME, font, IntToString(player[i]->weapon[2]->ammo), 10, 250, 250, 60);

		
		// Spell
		loadText(25 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Spell"), 16, 250, 250, 60);
		if (player[i]->isSpell == true && player[i]->spellUsed == false)
			loadImage(25 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)) + 8, Settings::CASE_SIZE + Settings::HEIGHT_GAME - 8, player[i]->spell.texture);
		// Score
		loadText(33 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 15 + Settings::HEIGHT_GAME, font, std::string("Score " + IntToString(player[i]->score)), 25, 250, 250, 60);
	}
}

void Graphic::affMap()
{
	int height_map = (Settings::HEIGHT) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;

	for (unsigned int i = 0; i < map.platform.size(); ++i)
	{
		for (unsigned int j = 0; j < map.platform[i]->length; ++j)
		{
			// Display
			loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y, map.platform[i]->texture[j], map.platform[i]->transp);
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
		loadImage(bulletList[i]->x, bulletList[i]->y, bulletList[i]->texture);
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
		loadImage(itemList[i]->x, itemList[i]->y, itemList[i]->texture);
	}
}

void Graphic::affPauseBG()
{
	loadImage(0, 0, ress.texture["pause"]);
}