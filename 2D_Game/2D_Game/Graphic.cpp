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
	loadText(18 * Settings::CASE_SIZE, 8 + Settings::HEIGHT_GAME, font, std::string(testDecade(min) + IntToString(min) + ":" + testDecade(sec) + IntToString(sec)), 32, 250, 180, 60);
	
	for (int i = 0; i < player.size(); ++i)
	{
		/*** Player n ***/
		loadText(Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Life"), 16, 250, 250, 60);
		// Life
		for (int j = 0; j < player[i]->life; ++j)
		{
			loadImage(Settings::CASE_SIZE + (j * ress.texture["life"].getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, ress.texture["life"]);
		}
		// Shield
		for (int k = player[i]->life; k < player[i]->life + player[i]->shield; ++k)
		{
			loadImage(Settings::CASE_SIZE + (k * ress.texture["shield"].getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, ress.texture["shield"]);
		}
		// Ammo
		loadText(6 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Ammo"), 16, 250, 250, 60);
		loadImage(6 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME - 4, ress.texture["ammoLogo"]);
		loadText(7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), Settings::CASE_SIZE + Settings::HEIGHT_GAME, font, IntToString(player[i]->weapon[0]->ammo), 16, 250, 250, 60);
		// Spell
		loadText(12 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 8 + Settings::HEIGHT_GAME, font, std::string("Spell"), 16, 250, 250, 60);
		if (player[i]->isSpell == true && player[i]->spellUsed == false)
			loadImage(12 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)) + 8, Settings::CASE_SIZE + Settings::HEIGHT_GAME - 8, player[i]->spell.texture);
		// Score
		loadText(25 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 12 + Settings::HEIGHT_GAME, font, std::string("Score " + IntToString(player[i]->score)), 25, 250, 250, 60);
	}
}

void Graphic::affMap()
{
	//loadImage(0, 0/* + Settings::HEIGHT_INTERFACE*/, ress.texture["background"]);


	int height_map = (Settings::HEIGHT/* + Settings::HEIGHT_INTERFACE*/) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;

	for (unsigned int i = 0; i < map.platform.size(); ++i)
	{
		for (unsigned int j = 0; j < map.platform[i]->length; ++j)
		{
			// Display
			if (map.platform[i]->isMorphing == true && (map.platform[i]->type == Platform::DISAPPEAR || map.platform[i]->type == Platform::APPEARING))
				if (j == 0)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Lplatform"], map.platform[i]->transp);
				else if (j == map.platform[i]->length -1)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Rplatform"], map.platform[i]->transp);
				else
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Mplatform"], map.platform[i]->transp);
			//else if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DAMAGE)
			//{
			//	if (j == 0)
			//		loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["LDplatform"]);
			//	else if (j == map.platform[i]->length -1)
			//		loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["RDplatform"]);
			//	else
			//		loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["MDplatform"]);
			//}
			else
			{
				if (j == 0)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Lplatform"]);
				else if (j == map.platform[i]->length -1)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Rplatform"]);
				else
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, ress.texture["Mplatform"]);
			}
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
		loadImage(bulletList[i]->x, bulletList[i]->y/* + Settings::HEIGHT_INTERFACE*/, bulletList[i]->texture);
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
		loadImage(itemList[i]->x, itemList[i]->y/* + Settings::HEIGHT_INTERFACE*/, itemList[i]->texture);
	}
}

void Graphic::affPauseBG()
{
	loadImage(0, 0/* + Settings::HEIGHT_INTERFACE*/, ress.texture["pause"]);
}