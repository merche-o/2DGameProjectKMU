#pragma once

#include <vector>
#include "AUnit.h"
#include "Item.h"
#include "Ressources.h"
#include "Settings.h"

class Spawner
{
private:
	enum e_posState {
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT
	};
	int posx;
	int posy;
	std::vector<AUnit*> & ennemies;
	std::vector<Item*> & itemList;
	void changePlaceSpawner();
	e_posState spawnPosState;
	float &loopTime;
public:

	Spawner(std::vector<AUnit*> & ennemyList, std::vector<Item *> &itemList, float &LoopTime);
	~Spawner(void);
	void spawnEnnemies(std::vector<AUnit*> &ennemy);
};

