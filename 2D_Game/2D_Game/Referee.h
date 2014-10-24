#pragma once

#include <vector>
#include <utility>
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"
#include "Settings.h"
#include "Bullet.h"

class Referee
{
public:
	int colliderCheck(AUnit  *,  Event::Input const &);
	bool applyGravity(AUnit *);
	void cleanEnemyList();
	void moveBullet();
	bool dealDamage(std::vector<Player *> &_player);
	Referee(std::vector<AUnit*> & enemylist, std::vector<Item*> &itemList, std::vector<Bullet *> &bulletList, Map  &map, float &LoopTime);
	~Referee();
	
private:
	Map  &_map;
	Player *tmp;
	float &loopTime;
	std::vector<AUnit*> & _enemyList;
	std::vector<Item*>  &_itemList;
	std::vector<Bullet*>  &_bulletList;
	void bulletHit();
	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit  *, Event::Input const &)> collideManager;


	void playerInvinsibility(Player *player);

	//movement collide function that return wich 
	int collideWall(AUnit  *, Event::Input const &);
	int collideBonus(AUnit  *, Event::Input const &);
	int collideEnemy(AUnit  *, Event::Input const &);

	//
};

