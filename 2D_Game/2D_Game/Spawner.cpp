// Olivier

#include "Spawner.h"
#include "Enemy.h"
#include <cstdlib>



Spawner::Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList, float &LoopTime)
	: ennemies(ennemyList), itemList(itemList), posx(-2), posy(0), currentWave(0), spawnPosState(UP_LEFT), loopTime(LoopTime)
{
	enemyWaves.push_back(EnemyWave(20,	1.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(10,	0.4,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(10,	0.0,	0.0,	0.0,	0.0));

	enemyWaves.push_back(EnemyWave(20,	1.3,	0.8,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(30,	1.0,	0.0,	1.0,	0.0));
	enemyWaves.push_back(EnemyWave(30,	1.0,	0.0,	0.0,	1.0));
	enemyWaves.push_back(EnemyWave(30,	1.0,	1.5,	1.7,	1.7));

	enemyWaves.push_back(EnemyWave(10,	0.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(30,	0.4,	0.8,	2.0,	2.0));
	enemyWaves.push_back(EnemyWave(10,	0.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(30,	1.8,	1.8,	0.9,	0.9));

	enemyWaves.push_back(EnemyWave(15,	0.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(10,	0.4,	0.4,	0.4,	0.4));
	enemyWaves.push_back(EnemyWave(20,	0.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(10,	0.4,	0.4,	0.4,	0.4));
	enemyWaves.push_back(EnemyWave(15,	0.0,	0.0,	0.0,	0.0));
	enemyWaves.push_back(EnemyWave(0,	0.47,	0.51,	0.53,	0.57));
}

Spawner::~Spawner(void)
{
}

void Spawner::changePlaceSpawner()
{
	if (spawnPosState == UP_LEFT){
		
		spawnPosState = UP_RIGHT;
		posx = Settings::WIDTH - (Settings::CASE_SIZE) - 2;
		posy = 2;
	}
	else if (spawnPosState == UP_RIGHT){
		spawnPosState = UP_LEFT;
		
		posx = 2;
		posy = 2;
	}
}

void Spawner::spawnEnnemies(std::vector<AUnit*> &ennemy, sf::Time globalTimer)
{
	e_dir dir;

	if (enemyWaves[currentWave].length != 0 && enemyWaves[currentWave].clock.getElapsedTime().asSeconds() >= enemyWaves[currentWave].length)
	{
		currentWave++;
		enemyWaves[currentWave].clock.restart();
	}
	for (int i = 0; i < ennemy.size(); i++)
	{
		ennemy[i]->spawn = ennemy[i]->timer.getElapsedTime();
		if (enemyWaves[currentWave].spawnTime[i] != 0 && ennemy[i]->spawn.asSeconds() >= ennemy[i]->spawnTime * enemyWaves[currentWave].spawnTime[i])
		{
			ennemy[i]->timer.restart();
		
			if (spawnPosState == UP_LEFT)
				dir = RIGHT;
			else
				dir = LEFT;
			ennemies.push_back(new Enemy(ennemy[i]->life, ennemy[i]->speed, ennemy[i]->damage, ennemy[i]->spawnTime, ennemy[i]->texture, posx, posy, dir, (enemyType)i, loopTime));
			changePlaceSpawner();
		}
	}
}

void Spawner::spawnAmmo(Player *src, sf::Texture texture, Map *map)
{
	e_dir dir;
	float x;
	float y;

	int i = 0;
	while (i < src->weapon.size())
	{
		src->weapon[i]->spawn = src->weapon[i]->timer.getElapsedTime();
		if (src->weapon[i]->spawn.asSeconds() >= src->weapon[i]->spawnTime)
			{
				src->weapon[i]->timer.restart();
				if (setAmmoSpawnerPos(map, x, y) == false)
					return;
				itemList.push_back(new Ammo(x, y, 5, loopTime, texture, Item::AMMO,src->weapon[i]->type));
				return;
			}
		i++;
	}
}

bool Spawner::setAmmoSpawnerPos(Map *map, float & x, float & y)
{
	int i;
	int r;

	srand(loopTime * time(NULL));

	// Check si platform pas au plafond
	i = rand() % map->platform.size();
	if (map->platform[i]->y == 0)
		return (false);

	// Assign Pos
	r = (rand() % (map->platform[i]->length - 1)) + 1;
	x = map->platform[i]->x + (r * Settings::CASE_SIZE);
	y = map->platform[i]->y - Settings::CASE_SIZE;


	// Si hors de map
	if (x < 0 && x > Settings::WIDTH)
	{
		x = Settings::WIDTH / 2;
		y = Settings::HEIGHT_GAME - (Settings::CASE_SIZE * 2);
	}
	
	return (true);
}

void Spawner::restart(void)
{
	currentWave = 0;
	enemyWaves[0].clock.restart();
}