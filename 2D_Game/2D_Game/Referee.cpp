#include "Referee.h"


Referee::Referee(std::vector<AUnit*> const& enemylist, std::vector<Item*> const &itemList, Map &map) 
: _enemyList(enemylist), _itemList(itemList), _map(map)
{
	//collideManager.a
	collideManager.push_back(&Referee::collideEnemy);
	collideManager.push_back(&Referee::collideBonus);
	collideManager.push_back(&Referee::collideWall);
}


Referee::~Referee()
{
}

int Referee::colliderCheck(AUnit const *src, Event::Input const &btn)
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

int 	Referee::collideBonus(AUnit const *src, Event::Input const &btn)
{
	return -1;
}

int Referee::collideWall(AUnit const *src, Event::Input const &btn)
{
	if (src->y + 5 > Settings::HEIGHT)
		return 1;
	//if (btn == Event::I_DOWN && this->_map.map[std::make_pair(src->y + 5, src->x)].type ==WALL)
//	{
	//	return 1;
	//}
	return -1;
}

int Referee::collideEnemy(AUnit const *src, Event::Input const &btn)
{
	
	return -1;
}