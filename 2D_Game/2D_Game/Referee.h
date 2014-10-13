#pragma once

#include <vector>
#include <utility>
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"
#include "Settings.h"

class Referee
{
public:
	int colliderCheck(AUnit  *,  Event::Input const &);
	bool applyGravity(AUnit *);
	void cleanEnemyList();
	void dealDamage(std::vector<Player *> &_player);
	Referee(std::vector<AUnit*> & enemylist, std::vector<Item*> const &itemList, Map  &map);
	~Referee();
	
private:
	Map  &_map;
	std::vector<AUnit*> & _enemyList;
	std::vector<Item*> const &_itemList;

	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit  *, Event::Input const &)> collideManager;

	//movement collide function that return wich 
	int collideWall(AUnit  *, Event::Input const &);
	int collideBonus(AUnit  *, Event::Input const &);
	int collideEnemy(AUnit  *, Event::Input const &);

	//
};

