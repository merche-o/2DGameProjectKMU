#include "PhysicEngine.h"


PhysicEngine::PhysicEngine(std::vector<Player *> &player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, Map  & map)
: _player(player), _ennemyList(enemylist), _itemList(itemList), _map(map)
{
	//actionManager

	actionManager[Event::I_UP] = &PhysicEngine::Jump;
	actionManager[Event::I_DOWN] = &PhysicEngine::moveDown;
	actionManager[Event::I_LEFT] = &PhysicEngine::moveLeft;
	actionManager[Event::I_RIGHT] = &PhysicEngine::moveRight;
	actionManager[Event::I_FIRE_UP] = &PhysicEngine::shootUp;
	actionManager[Event::I_FIRE_DOWN] = &PhysicEngine::shootDown;
	actionManager[Event::I_FIRE_LEFT] = &PhysicEngine::shootLeft;
	actionManager[Event::I_FIRE_RIGHT] = &PhysicEngine::shootRight;
	actionManager[Event::I_BONUS] = &PhysicEngine::useBonus;

}

PhysicEngine::~PhysicEngine(void)
{
}

void PhysicEngine::playerAction(int playerId)
{
	unsigned int i = 0;

	while ( i < this->_player[playerId]->inputMap.size())
	{
		
		if (this->_player[playerId]->inputMap[i] == true)
			(this->*(actionManager[(Event::Input)i]))(_player[playerId]);
		++i;
	}
	gravity(this->_player[playerId]);
	
}

void PhysicEngine::moveLeft(AUnit *src)
{
	if(_referee->colliderCheck(src, Event::Input::I_LEFT) == -1)
		src->x -= src->speed;
}


void PhysicEngine::moveRight(AUnit *src)
{
	if (_referee->colliderCheck(src, Event::Input::I_RIGHT) == -1)
		src->x += src->speed;
}

void PhysicEngine::Jump(AUnit *src)
{
	return;
}

void PhysicEngine::moveDown(AUnit *src)
{
	return;
}

void PhysicEngine::useBonus(AUnit *src)
{
	return;
}

void PhysicEngine::shootUp(AUnit *src)
{
	return;
}

void PhysicEngine::shootDown(AUnit *src)
{
	return;
}

void PhysicEngine::shootLeft(AUnit *src)
{
	return;
}

void PhysicEngine::shootRight(AUnit *src)
{
	return;
}

void PhysicEngine::gravity(AUnit *src) 
{
	//gravity
	//if (_referee->colliderCheck(src, Event::Input::I_DOWN) == -1)
		//src->y += 5;
	return;
}