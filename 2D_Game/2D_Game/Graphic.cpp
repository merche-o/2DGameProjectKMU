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
	sf::Texture texture;
	texture.loadFromFile("./Ressources/Images/Interface.png");
	loadImage(0, 0 + Settings::HEIGHT_GAME, texture);

	/*** Chrono ***/
	time += loopTime;
	float t = floor(time);
	int min = (int)t / 60;
	int sec = (int)t % 60;
	loadText(18 * Settings::CASE_SIZE, 0 + Settings::HEIGHT_GAME, font, std::string(testDecade(min) + IntToString(min) + ":" + testDecade(sec) + IntToString(sec)), 32, 250, 180, 60);
	
	for (int i = 0; i < player.size(); ++i)
	{
		/*** Player n ***/
		loadText(1 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 0 + Settings::HEIGHT_GAME, font, std::string("Player" + IntToString(i + 1)), 32, 250, 250, 60);
		// Score
		loadText(4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 0 + Settings::HEIGHT_GAME, font, std::string("Score " + IntToString(player[i]->score)), 32, 250, 250, 60);
		// Ammo
		texture.loadFromFile("./Ressources/Images/IAmmo.png");
		loadImage(4 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, texture);
		loadText(5 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, font, IntToString(player[i]->weapon[0]->ammo), 32, 250, 250, 60);
		// Life
		texture.loadFromFile("./Ressources/Images/LifeBar.png");
		for (int j = 0; j < player[i]->life; ++j)
		{
			loadImage(1 * Settings::CASE_SIZE + (j * texture.getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, texture);
		}
		// Shield
		texture.loadFromFile("./Ressources/Images/ShieldBar.png");
		for (int k = player[i]->life; k < player[i]->life + player[i]->shield; ++k)
		{
			loadImage(1 * Settings::CASE_SIZE + (k * texture.getSize().x) + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, texture);
		}
		// Spell
		if (player[i]->isSpell == true)
			loadText(7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 0 + Settings::HEIGHT_GAME, font, std::string("Spell"), 32, 250, 250, 60);
			loadImage(7 * Settings::CASE_SIZE + (i * (20 * Settings::CASE_SIZE)), 1 * Settings::CASE_SIZE + Settings::HEIGHT_GAME, player[i]->spell.texture);
	}
}

void Graphic::affMap()
{
	sf::Texture Background;
	Background.loadFromFile("./Ressources/Images/BackgroundGame.png");
	loadImage(0, 0/* + Settings::HEIGHT_INTERFACE*/, Background);


	int height_map = (Settings::HEIGHT/* + Settings::HEIGHT_INTERFACE*/) / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;
	
	sf::Texture Ltexture;
	sf::Texture Mtexture;
	sf::Texture Rtexture;
	Ltexture.loadFromFile("./Ressources/Images/L_Platform.png");
	Mtexture.loadFromFile("./Ressources/Images/M_Platform.png");
	Rtexture.loadFromFile("./Ressources/Images/R_Platform.png");

	for (unsigned int i = 0; i < map.platform.size(); ++i)
	{
		for (unsigned int j = 0; j < map.platform[i]->length; ++j)
		{
			// Display
			if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DISAPPEAR)
				if (j == 0)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Ltexture, map.platform[i]->transp);
				else if (j == map.platform[i]->length -1)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Rtexture, map.platform[i]->transp);
				else
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Mtexture, map.platform[i]->transp);
			else if (map.platform[i]->isMorphing == true && map.platform[i]->type == Platform::DAMAGE)
			{
				sf::Texture LDtexture;
				sf::Texture MDtexture;
				sf::Texture RDtexture;
				LDtexture.loadFromFile("./Ressources/Images/L_Dmg_Platform.png");
				MDtexture.loadFromFile("./Ressources/Images/M_Dmg_Platform.png");
				RDtexture.loadFromFile("./Ressources/Images/R_Dmg_Platform.png");
				if (j == 0)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, LDtexture);
				else if (j == map.platform[i]->length -1)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, RDtexture);
				else
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, MDtexture);
			}
			else
			{
				if (j == 0)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Ltexture);
				else if (j == map.platform[i]->length -1)
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Rtexture);
				else
					loadImage(map.platform[i]->x + (j * (float)Settings::CASE_SIZE), map.platform[i]->y/* + Settings::HEIGHT_INTERFACE*/, Mtexture);
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
	sf::Texture texture;

	texture.loadFromFile("./Ressources/Images/pause_bg.png");
	loadImage(0, 0/* + Settings::HEIGHT_INTERFACE*/, texture);
}