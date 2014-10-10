#include "PhysicEngine.h"


PhysicEngine::PhysicEngine(std::vector<Player *> &player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, Map & map)
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

	releaseActionManager[Event::I_UP] = &PhysicEngine::RJump;
	releaseActionManager[Event::I_DOWN] = &PhysicEngine::RmoveDown;
	releaseActionManager[Event::I_LEFT] = &PhysicEngine::RmoveLeft;
	releaseActionManager[Event::I_RIGHT] = &PhysicEngine::RmoveRight;
	releaseActionManager[Event::I_FIRE_UP] = &PhysicEngine::RshootUp;
	releaseActionManager[Event::I_FIRE_DOWN] = &PhysicEngine::RshootDown;
	releaseActionManager[Event::I_FIRE_LEFT] = &PhysicEngine::RshootLeft;
	releaseActionManager[Event::I_FIRE_RIGHT] = &PhysicEngine::RshootRight;
	releaseActionManager[Event::I_BONUS] = &PhysicEngine::RuseBonus;

	gravityMax = 30;	
}

PhysicEngine::~PhysicEngine(void)
{
}

void PhysicEngine::enemyAction()
{
	int i = 0;
	int i2 = 0;

	while (i < this->_ennemyList.size())
		{
			while ( i2 < this->_ennemyList[i]->inputMap.size())
				{
					if (this->_ennemyList[i]->inputMap[i2] == true)
					(this->*(actionManager[(Event::Input)i2]))(this->_ennemyList[i]);
						if (this->_ennemyList[i]->inputMap[i2] == false)
					(this->*(releaseActionManager[(Event::Input)i2]))(this->_ennemyList[i]);

					i2++;
				}
			gravity(this->_ennemyList[i]);
			++i;
		}

}


void PhysicEngine::playerAction(int playerId)
{
	unsigned int i = 0;
	
	while ( i < this->_player[playerId]->inputMap.size())
	{
		
		if (this->_player[playerId]->inputMap[i] == true)
			(this->*(actionManager[(Event::Input)i]))(_player[playerId]);
		if (this->_player[playerId]->inputMap[i] == false)
			(this->*(releaseActionManager[(Event::Input)i]))(_player[playerId]);

		++i;
	}
	gravity(this->_player[playerId]);
	
}

void PhysicEngine::moveLeft(AUnit *src)
{
	if(_referee->colliderCheck(src, Event::I_LEFT) == -1)
		src->x -= (src->speed + 10);
}


void PhysicEngine::moveRight(AUnit *src)
{
	if (_referee->colliderCheck(src, Event::I_RIGHT) == -1)
		src->x += (src->speed + 10);
}

void PhysicEngine::Jump(AUnit *src)
{
	
	if (_referee->colliderCheck(src, Event::I_UP) == -1)
		{
			if (src->state == U_JUMP)
			{
				src->y -= 15 + src->fallingSpeed;
				src->jumpTmpY -= 15 + src->fallingSpeed;
			}
			if (src->state == U_NORMAL)
				src->state = U_JUMP;/*
			else if(src->state == U_END_JUMP)
				src->state = U_JUMP;*/
			if (src->jumpTmpY + Settings::HIGH_JUMP <= 0)
				src->state = U_END_JUMP;
			
		}
	if (_referee->colliderCheck(src, Event::I_UP) == 1)
		src->state = U_END_JUMP;
	return;
}

//Push button
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


//Release button

void PhysicEngine::RmoveLeft(AUnit *src)
{
	return;
}


void PhysicEngine::RmoveRight(AUnit *src)
{
	return;
}

void PhysicEngine::RJump(AUnit *src)
{
	/*if (src->state == U_JUMP)
		src->state = U_END_JUMP;*/
	if (_referee->applyGravity(src) == false)
	{
		src->jumpTmpY = 0;
		src->state = U_NORMAL;
	}
	return;
}

void PhysicEngine::RmoveDown(AUnit *src)
{				   
	return;		   
}				   
				   
void PhysicEngine::RuseBonus(AUnit *src)
{				   
	return;		   
}				   
				   
void PhysicEngine::RshootUp(AUnit *src)
{				   
	return;		   
}				   
				   
void PhysicEngine::RshootDown(AUnit *src)
{				   
	return;		   
}				   
				   
void PhysicEngine::RshootLeft(AUnit *src)
{				   
	return;		   
}				   
				   
void PhysicEngine::RshootRight(AUnit *src)
{
	return;
}


//Physics


void PhysicEngine::gravity(AUnit *src) 
{
	if (_referee->applyGravity(src) == true)
	{
		src->y += src->fallingSpeed;
		if (src->fallingSpeed < gravityMax)
			src->fallingSpeed += 3;
	}
	else
	{
		src->fallingSpeed = 5;
	}
		//src->y += Settings::GRAVITY;
	return;
}