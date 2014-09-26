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
	
	void playerAction(int playerId,std::vector<bool> const &); 
	void enemyAction();
	void mapMove();
	void projectileMove();

	PhysicEngine(std::vector<Player> player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, Map const & map, Referee &referee);
	~PhysicEngine(void);

private:
	std::vector<Player> _player;
	std::vector<AUnit*> _ennemyList;
	std::vector<Item*> _itemList;
	std::map<Event::Input, void(PhysicEngine:: *)(AUnit &src)> actionManager;
	Map const _map;
	Referee &_referee;
	//call after Checking collider
	void doAction();

	//Universal action
	void moveLeft(AUnit &src);
	void moveRight(AUnit &src);
	void moveDown(AUnit &src);
	void Jump(AUnit &src);

	// Player Action
	void shootUp(AUnit &src);
	void shootDown(AUnit &src);
	void shootRight(AUnit &src);
	void shootLeft(AUnit &src);
	void useBonus(AUnit &src);
	 

	//-----Passive Action

	//DamageManager
	void dealDammage();
	void BulletDammage();
	void EnemiesDammage();
	void PlayerDammage();

	//BonusManager - Have to complete in function of implemented bonus
	void getBonus();

	
	



};

