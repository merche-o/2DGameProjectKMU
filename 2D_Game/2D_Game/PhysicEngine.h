#pragma once

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

	PhysicEngine(Player const player[2], std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, Map const & map);
	~PhysicEngine(void);

private:
	Player player[2];
	std::vector<AUnit*> _ennemyList;
	std::vector<Item*> _itemList;
	std::vector<bool> _moveList;
	std::map<bool, void(PhysicEngine:: * )()> actionManager;
	Map const _map;
	
	//call after Checking collider
	void doAction();

	//Universal action
	void moveLeft();
	void moveRight();
	void moveDown();
	void Jump();

	// Player Action
	void shootUp();
	void shootDown();
	void shootRight();
	void shootLeft();
	void useBonus();
	 

	//-----Passive Action

	//DamageManager
	void dealDammage();
	void BulletDammage();
	void EnemiesDammage();
	void PlayerDammage();

	//BonusManager - Have to complete in function of implemented bonus
	void getBonus();

	
	



};

