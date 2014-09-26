#pragma once

#include <vector>
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"

class Referee
{
	

public:
	int colliderCheck(AUnit const &,  Event::Input const &);

	Referee(std::vector<AUnit*> const& enemylist, std::vector<Item*> const &itemList, Map const &map);
	~Referee();
	
private:
	Map const _map;
	std::vector<AUnit*> const &_enemyList;
	std::vector<Item*> const &_itemList;

	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit const &, Event::Input const &)> collideManager;

	//collide function that return wich 
	int collideWall(AUnit const &, Event::Input const &);
	int collideBonus(AUnit const &, Event::Input const &);
	int collideEnemy(AUnit const &, Event::Input const &);
};

