#pragma once

#include "SFML\System\Clock.hpp"
#include <vector>
#include <map>
#include "Settings.h"
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"
#include "Referee.h"
#include "Bullet.h"
#include <iostream>

class PhysicEngine
{
	//Enum to put in Event
public:
	void playerAction(int playerId); 
	void enemyAction();
	void mapMove();
	void projectileMove();
	Referee *_referee;
	SoundEngine &_sound;
	PhysicEngine(std::vector<Player *> &player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList, Map  &map, float  &LoopTime, SoundEngine &sound);
	~PhysicEngine(void);

private:
	std::vector<Player *> &_player;
	std::vector<AUnit*> &_ennemyList;
	std::vector<Item*> &_itemList;
	std::vector<Bullet *> &_bulletList;
	std::map<Event::Input, void(PhysicEngine:: *)(AUnit *src)> actionManager;
	std::map<Event::Input, void(PhysicEngine:: *)(AUnit *src)> releaseActionManager;
	Map  &_map;
	float &loopTime;
	int gravityMax;
	
	//call after Checking collider
	void doAction();

	//Universal action
	void moveLeft(AUnit *src);
	void moveRight(AUnit *src);
	void moveDown(AUnit *src);
	void Jump(AUnit *src);

	// Player Action
	void shootUp(AUnit *src);
	void shootDown(AUnit *src);
	void shootRight(AUnit *src);
	void shootLeft(AUnit *src);
	void useBonus(AUnit *src);
	void swapSpell(AUnit *src);
	 

	//-----Passive Action

	//DamageManager
	void dealDammage();
	void BulletDammage();
	void EnemiesDammage();
	void PlayerDammage();

	//BonusManager - Have to complete in function of implemented bonus
	void getBonus();

	void collide(AUnit *src);

	
	//ReleaseAction

	
	void RmoveLeft(AUnit *src);
	void RmoveRight(AUnit *src);
	void RmoveDown(AUnit *src);
	void RJump(AUnit *src);

	// Player Action
	void RshootUp(AUnit *src);
	void RshootDown(AUnit *src);
	void RshootRight(AUnit *src);
	void RshootLeft(AUnit *src);
	void RuseBonus(AUnit *src);
	void RswapSpell(AUnit *src);


};

