#include "PhysicEngine.h"


PhysicEngine::PhysicEngine(Player const player[2], std::vector<AUnit*>  &_enemylist, std::vector<Item*>  &itemList, Map const & map) : _ennemyList(_enemylist), _itemList(itemList), _map(map)
{
	/*actionManager[Event::UP] = &Jump;
	actionManager[Event::DOWN] = &moveDown;
	actionManager[Event::LEFT] = &moveLeft;
	actionManager[Event::RIGHT] = &moveRight;
	actionManager[Event::FIRE_UP] = &shootUp;
	actionManager[Event::FIRE_DOWN] = &shootDown;
	actionManager[Event::FIRE_LEFT] = &shootLeft;
	actionManager[Event::FIRE_RIGHT] = &shootRight;
	actionManager[Event::BONUS] = &useBonus;
	*/

}

PhysicEngine::~PhysicEngine(void)
{
}

void PhysicEngine::playerAction(int playerId, std::vector<bool> const &input, Referee const &ref)
{
/*	int i = 0;
	while (i < input.max_size)
	{
		if (input[i] == true)
			(this->*(actionManager[(Event::Input)i]))();
		++i;
	}
	*/
}

//void PhysicEngine::moveLeft(AUnit &src)
//{
//	src.x
//}
