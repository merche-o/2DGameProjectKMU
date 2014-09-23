#pragma once

#include <list>
#include "Settings.h"
#include "Player.h"
#include "Item.h"
#include "Map.h"

class PhysicEngine
{
	void playerAction();
	void enemyAction();
	void mapMove();
	void projectileMove();

private:
	Player player[2];
	std::list<AUnit*> ennemyList;
	std::list<Item*> itemList;
	void checkCollider();
	void callReaction(); //make change on depend of the collision ---> other class ?

	PhysicEngine(void);
	~PhysicEngine(void);
};

