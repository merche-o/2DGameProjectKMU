#include "Spawner.h"



Spawner::Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList)
	: ennemies(ennemyList), itemList(itemList)
{
}

Spawner::~Spawner(void)
{
}

void Spawner::spawnEnemies(std::vector <AUnit*> ennemy)
{
	for (int i = 0; i < ennemy.size(); i++)
	{
		ennemy[i]->spawn = ennemy[i]->timer.getElapsedTime();
		if (ennemy[i]->spawn.asSeconds() >= ennemy[i]->spawnTime)
		{
			ennemy[i]->timer.restart();
			ennemy[i]->x = 100;
			ennemy[i]-> y = 100;
			ennemies.push_back(ennemy[i]);
		}
	}
}
