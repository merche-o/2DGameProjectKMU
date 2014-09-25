#pragma once

#include <list>
#include <vector>
#include <map>
#include "Settings.h"
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"
#include "Referee.h"

class PhysicEngine
{
	//Enum tu put in Event
	
	void playerAction(int playerId,std::vector<bool> const &, Referee const &); 
	void enemyAction();
	void mapMove();
	void projectileMove();

	PhysicEngine(/*Player const player[2], std::list<AUnit*>  &enemylist, std::list<Item*>  &itemList, Map const & map*/);
	~PhysicEngine(void);

private:
	Player player[2];
	std::list<AUnit*> ennemyList;
	std::list<Item*> itemList;
	std::vector<bool> moveList;
	//std::map<bool, void(PhysicEngine:: &)()> actionManager;
	Map const map;
	
	//call after Checking collider
	void doAction();

	//Universal action
	void moveLeft();
	void moveRight();
	void MoveDown();
	void Jump();

	// Player Action
	void shootUp();
	void shootDown();
	void shootRight();
	void shootLeft();
	 

	//-----Passive Action

	//DamageManager
	void dealDammage();
	void BulletDammage();
	void EnemiesDammage();
	void PlayerDammage();

	//BonusManager - Have to complete in function of implemented bonus
	void getBonus();

	
	



};

