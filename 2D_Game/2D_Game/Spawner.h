#pragma once

#include <vector>
#include "AUnit.h"
#include "Enemy.h"
#include "Item.h"
#include "Ammo.h"
#include "Ressources.h"
#include "Settings.h"
#include "Player.h"
#include "Map.h"

class Spawner
{
private:
	enum e_posState
	{
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT
	};

private:
	int posx;
	int posy;
	std::vector<AUnit*> & ennemies;
	std::vector<Item*> & itemList;
	void changePlaceSpawner();
	e_posState spawnPosState;
	float &loopTime;
	std::map<enemyType, int> enemyLuckToSpawn;

	enemyType randEnnemyType(AUnit *);
	

public:
	Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList, float &LoopTime);
	~Spawner(void);
	void spawnEnnemies(std::vector<AUnit*> &ennemy);
	void spawnAmmo(Player *, sf::Texture texture, Map *map);
	bool setAmmoSpawnerPos(Map *map, float &x, float &y);
};

