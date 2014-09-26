#include "PhysicEngine.h"


PhysicEngine::PhysicEngine(std::vector<Player> player, std::vector<AUnit*>  &_enemylist, std::vector<Item*>  &itemList, Map const & map, Referee  &referee)
: _player(player), _ennemyList(_enemylist), _itemList(itemList), _map(map), _referee(referee)
{
	actionManager[Event::UP] = &PhysicEngine::Jump;
	actionManager[Event::DOWN] = &PhysicEngine::moveDown;
	actionManager[Event::LEFT] = &PhysicEngine::moveLeft;
	actionManager[Event::RIGHT] = &PhysicEngine::moveRight;
	actionManager[Event::FIRE_UP] = &PhysicEngine::shootUp;
	actionManager[Event::FIRE_DOWN] = &PhysicEngine::shootDown;
	actionManager[Event::FIRE_LEFT] = &PhysicEngine::shootLeft;
	actionManager[Event::FIRE_RIGHT] = &PhysicEngine::shootRight;
	actionManager[Event::BONUS] = &PhysicEngine::useBonus;

}

PhysicEngine::~PhysicEngine(void)
{
}

void PhysicEngine::playerAction(int playerId, std::vector<bool> const &input)
{
	unsigned int i = 0;

	while ( i < input.size())
	{
		if (input[i] == true)
			(this->*(actionManager[(Event::Input)i]))(_player[playerId]);
		++i;
	}
	
}

void PhysicEngine::moveLeft(AUnit &src)
{
	if(_referee.colliderCheck(src, Event::Input::LEFT) == -1)
		src.x += 5;
}


void PhysicEngine::moveRight(AUnit &src)
{
	if (_referee.colliderCheck(src, Event::Input::RIGHT) == -1)
		src.x -= 5;
}

void PhysicEngine::Jump(AUnit &src)
{
	return;
}

void PhysicEngine::moveDown(AUnit &src)
{
	return;
}

void PhysicEngine::useBonus(AUnit &src)
{
	return;
}

void PhysicEngine::shootUp(AUnit &src)
{
	return;
}

void PhysicEngine::shootDown(AUnit &src)
{
	return;
}

void PhysicEngine::shootLeft(AUnit &src)
{
	return;
}

void PhysicEngine::shootRight(AUnit &src)
{
	return;
}
