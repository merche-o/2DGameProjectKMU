// Olivier

#include "Spawner.h"
#include "Enemy.h"
#include <cstdlib>



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

			ennemies.push_back(new Enemy(ennemy[i]->life, ennemy[i]->speed, ennemy[i]->damage, ennemy[i]->spawnTime, ennemy[i]->texture, posx, posy, dir, enemy_type(rand() % 2), loopTime));
			changePlaceSpawner();
		}
	}

	
}

void Spawner::spawnAmmo(Player *src, sf::Texture texture, Map *map)
{
	e_dir dir;
	float x;
	float y;
	// mettre un timer de pop ammo dans la weapon dans ressources, se baser dessus pour pop les ammo de l'arme en question
	int i= 0;
	while (i < src->weapon.size())
		{
			src->weapon[i]->spawn = src->weapon[i]->timer.getElapsedTime();
			if (src->weapon[i]->spawn.asSeconds() >= src->weapon[i]->spawnTime)
				{
					src->weapon[i]->timer.restart();
					if (setAmmoSpawnerPos(map,x , y) == false)
						return;
					itemList.push_back(new Ammo(x, y, 5,loopTime, texture, Item::AMMO,src->weapon[i]->type));
			}
		
			i++;
		}
	
	
}

bool Spawner::setAmmoSpawnerPos(Map *map, float &x, float &y)
{
int i;

i = map->platform.size();
srand(loopTime * 100000);
if (i == 0)
	return false;
i = rand() %i;
if (i == 0)
	return false;
x = map->platform[i]->x + ((map->platform[i]->length * Settings::CASE_SIZE) /2);
				y = map->platform[i]->y - Settings::CASE_SIZE;
return true;
}