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
	int colliderCheck(AUnit const *,  Event::Input const &);
	bool applyGravity(AUnit const *);
	Referee(std::vector<AUnit*> const& enemylist, std::vector<Item*> const &itemList, Map  &map);
	~Referee();
	
private:
	Map  &_map;
	std::vector<AUnit*> const &_enemyList;
	std::vector<Item*> const &_itemList;

	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit const *, Event::Input const &)> collideManager;

	//collide function that return wich 
	int collideWall(AUnit const *, Event::Input const &);
	int collideBonus(AUnit const *, Event::Input const &);
	int collideEnemy(AUnit const *, Event::Input const &);
};

