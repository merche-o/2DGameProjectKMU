#include "PhysicEngine.h"


PhysicEngine::PhysicEngine(std::vector<Player *> &player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList, Map & map, float  &LoopTime)
: _player(player), _ennemyList(enemylist), _itemList(itemList), _bulletList(bulletList), _map(map), loopTime(LoopTime)
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

	gravityMax = 25 * Settings::CASE_SIZE;	
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
			i2 = 0;
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
	for (unsigned int i = 0; i < this->_player[playerId]->inputMap.size(); ++i)
	{
		if (this->_player[playerId]->inputMap[i] == true)
			(this->*(actionManager[(Event::Input)i]))(_player[playerId]);
		if (this->_player[playerId]->inputMap[i] == false)
			(this->*(releaseActionManager[(Event::Input)i]))(_player[playerId]);
		this->_player[playerId]->updateClock();
	}
	gravity(this->_player[playerId]);
}

void PhysicEngine::moveLeft(AUnit *src)
{
	src->x -= (src->speed * src->loopTime);
	src->nextFrame();
}

void PhysicEngine::moveRight(AUnit *src)
{
	src->x += (src->speed *src->loopTime);
	src->nextFrame();
}

void PhysicEngine::Jump(AUnit *src)
{
	if (_referee->colliderCheck(src, Event::I_UP) == -1)
		{
			/*if (src->doubleJump == true)
			{
				src->doubleJump = false;
				src->jumpTmpY /= 3;
				Jump(src);
			}*/
			if (src->state == U_JUMP)
			{
				src->y -= (20) * Settings::CASE_SIZE * (src->loopTime)  ;
				src->jumpTmpY -= (20) * Settings::CASE_SIZE * (src->loopTime);
			}
			if (src->state == U_NORMAL)
			{
				src->act = JUMP;
				src->state = U_JUMP;
			}/*
			else if(src->state == U_END_JUMP)
				src->state = U_JUMP;*/
			if (src->jumpTmpY + Settings::HIGH_JUMP <= 0)
				src->state = U_END_JUMP;			
			
		}
	if (_referee->colliderCheck(src, Event::I_UP) == 1)
	{
		src->state = U_END_JUMP;
	}
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
	if (src->fireRateCount <= 0.f)
		{
			src->fireRateCount = src->fireRate;
			this->_bulletList.push_back(new Bullet(src->x + (src->width /2), src->y ,10,5, 0, -1, 10, loopTime, src));
		}
	return;
}

void PhysicEngine::shootDown(AUnit *src)
{
	return;
}

void PhysicEngine::shootLeft(AUnit *src)
{
	if (src->fireRateCount <= 0.f)
		{
			src->fireRateCount = src->fireRate;
			this->_bulletList.push_back(new Bullet(src->x, src->y + (src->height /2),10,5,-1, 0, 10,  loopTime, src));	
		}
	
	return;
}

void PhysicEngine::shootRight(AUnit *src)
{
	if (src->fireRateCount <= 0.f)
		{
			src->fireRateCount = src->fireRate;
			this->_bulletList.push_back(new Bullet(src->x + src->width, src->y + (src->height /2),10,5,1,0, 10, loopTime,src));
		}
	return;
}


//Release button

void PhysicEngine::RmoveLeft(AUnit *src)
{
	src->animFrame = 1;
	return;
}


void PhysicEngine::RmoveRight(AUnit *src)
{
	src->animFrame = 1;
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
		src->act = WALK;
	}
	else
	{
		src->act = JUMP;
		src->state = U_JUMP;
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
	_referee->colliderCheck(src, Event::I_NONE);
	if (_referee->applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		if (src->fallingSpeed < gravityMax)
			src->fallingSpeed += ((5 * Settings::CASE_SIZE)  * (src->loopTime));
		_referee->applyGravity(src);
	}
	else
	{
		src->fallingSpeed = 5 * Settings::CASE_SIZE;
		//src->doubleJump = true;
	}
	return;
}