#pragma once

#include <list>
#include <vector>
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"

class Referee
{
	enum collideType {
		ENEMY,
		BONUS,
		WALL,
		NOTHING,
	};

public:
	AUnit &colliderCheck(AUnit const &, enum Input const &);

	
	Referee(std::list<AUnit*> const& enemylist, std::list<Item*> const &itemList, Map const &map);
	~Referee();
	
private:
	Map const Map;
	std::list<AUnit*> const &ennemyList;
	std::list<Item*> const &itemList;

	//call collider in function of the collide Type (loop) 
	std::map<collideType, AUnit &(Referee:: &)(AUnit const &, Input const &)> collideManager;

	//collide function that return wich 
	AUnit &collideWall(AUnit const &, Input const &);
	AUnit &collideBonus(AUnit const &, Input const &);
	AUnit &collideEnemy(AUnit const &, Input const &);
};

