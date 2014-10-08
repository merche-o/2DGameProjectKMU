#include "Spawner.h"



Spawner::Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList)
	: ennemies(ennemyList), itemList(itemList)
{
}

Spawner::~Spawner(void)
{
}

void Spawner::spawnEnnemies(std::vector <AUnit*> ennemy)
{
	for (int i = 0; i < ennemy.size(); i++)
	{
		ennemy[i]->spawn = ennemy[i]->timer.getElapsedTime();
		if (ennemy[i]->spawn.asSeconds() >= ennemy[i]->spawnTime)
		{
			ennemy[i]->timer.restart();
			
				ennemies.push_back(ennemy[i]);
		}
	}
}
