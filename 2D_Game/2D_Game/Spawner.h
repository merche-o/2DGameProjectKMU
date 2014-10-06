#pragma once

#include <vector>
#include "AUnit.h"
#include "Item.h"
#include "Ressources.h"

class Spawner
{
private:
	std::vector<AUnit*> & ennemies;
	std::vector<Item*> & itemList;

public:

	Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList);
	~Spawner(void);
	void spawnEnnemies(std::vector<AUnit*> ennemy);
};

