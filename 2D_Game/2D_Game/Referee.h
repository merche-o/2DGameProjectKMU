#pragma once

#include <vector>
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"

class Referee
{
	

public:
	int colliderCheck(AUnit &,  Event::Input &);

	Referee(std::vector<AUnit*> & enemylist, std::vector<Item*> &itemList, Map &map);
	~Referee();
	
private:
	Map const _map;
	std::vector<AUnit*> &_enemyList;
	std::vector<Item*> &_itemList;

	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit &, Event::Input &)> collideManager;

	//collide function that return wich 
	int collideWall(AUnit &, Event::Input &);
	int collideBonus(AUnit &, Event::Input &);
	int collideEnemy(AUnit &, Event::Input &);
};

