#pragma once

#include <vector>
#include "Display.h"
#include "Map.h"
#include "Player.h"
#include "Ressources.h"
#include "Item.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	Map & map;
	std::vector<Player*> & player;
	std::vector<AUnit*> & ennemyList;
	std::vector<Bullet*> & bulletList;
	std::vector<Item *> &itemList;
	Ressources & ress;
	float & loopTime;
	float time;

public:
	Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p, std::vector<AUnit*> & ennemyList, std::vector<Bullet*> & b, std::vector<Item*> &ItemList, Ressources & ressource, float & Time);
	~Graphic(void);

	void RefreshWindow();
	void affInterface();
	void affMap();
	void affUnits();
	void affBullets();
	void affSpell();
	void affItems();
	void resetInterface();
};

