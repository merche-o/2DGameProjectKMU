#include "Spawner.h"
#include "Enemy.h"



Spawner::Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList, float &LoopTime)
	: ennemies(ennemyList), itemList(itemList), posx(-2), posy(0), spawnPosState(UP_LEFT), loopTime(LoopTime)
{
}

Spawner::~Spawner(void)
{
}

void Spawner::changePlaceSpawner()
{
	if (spawnPosState == UP_LEFT){
		
		spawnPosState = UP_RIGHT;
		posx = Settings::WIDTH - (Settings::CASE_SIZE) + 2;
		posy = 0;
	}
	else if (spawnPosState == UP_RIGHT){
		spawnPosState = UP_LEFT;
		
		posx = -2;
		posy = 0;
	}
}

void Spawner::spawnEnnemies(std::vector <AUnit*> &ennemy)
{
	e_dir dir;
	
	for (int i = 0; i < ennemy.size(); i++)
	{
		ennemy[i]->spawn = ennemy[i]->timer.getElapsedTime();
		if (ennemy[i]->spawn.asSeconds() >= ennemy[i]->spawnTime)
		{
			ennemy[i]->timer.restart();
		
			if (spawnPosState == UP_LEFT)
				dir = RIGHT;
			else
				dir = LEFT;

			ennemies.push_back(new Enemy(ennemy[i]->life, ennemy[i]->speed, ennemy[i]->damage, ennemy[i]->spawnTime, ennemy[i]->texture, posx, posy, dir, E_BASIC, loopTime));
			changePlaceSpawner();
		}
	}

	
}

void Spawner::spawnAmmo()
{
	e_dir dir;

	// mettre un timer de pop ammo dans la weapon dans ressources, se baser dessus pour pop les ammo de l'arme en question

	//itemList.push_back(new Ammo());
	changePlaceSpawner();
}