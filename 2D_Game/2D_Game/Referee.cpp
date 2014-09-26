#include "Referee.h"


Referee::Referee(std::vector<AUnit*> & enemylist, std::vector<Item*>  &itemList, Map  &map) 
: _enemyList(enemylist), _itemList(itemList), _map(map)
{
	collideManager[0] = &Referee::collideEnemy;
	collideManager[1] = &Referee::collideBonus;
	collideManager[2] = &Referee::collideWall;
}


Referee::~Referee()
{
}

int Referee::colliderCheck(AUnit &src, Event::Input &btn)
{
	int i = 0;
	bool touch = false;
	int target = -1;
	while (i < 3)
	{
		if ( (target =(this->*(collideManager[i]))(src,btn)) != -1)
			return target;
		++i;
	}
	return -1;
}

int 	Referee::collideBonus(AUnit &src, Event::Input &btn)
{
	return -1;
}

int Referee::collideWall(AUnit &src, Event::Input &btn)
{
	
	return -1;
}

int Referee::collideEnemy(AUnit &src, Event::Input &btn)
{
	
	return -1;
}