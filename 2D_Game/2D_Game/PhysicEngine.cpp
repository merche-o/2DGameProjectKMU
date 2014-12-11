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

	gravityMax = 28 * Settings::CASE_SIZE;	
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
			++i;
		}
}


void PhysicEngine::playerAction(int playerId)
{
	this->_player[playerId]->prevX = this->_player[playerId]->x;
	this->_player[playerId]->prevY = this->_player[playerId]->y;
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
			if (src->doubleJump == true && src->state == U_END_JUMP)
			{
				src->doubleJump = false;
				src->jumpTmpY += (32) * Settings::CASE_SIZE * (src->loopTime);
				src->state = U_NORMAL;
			}
			if (src->state == U_JUMP)
			{
				src->jumpTmpY -= (32) * Settings::CASE_SIZE * (src->loopTime);
				src->y -= (24) * Settings::CASE_SIZE * (src->loopTime);
			}
			if (src->state == U_NORMAL)
			{
				src->act = JUMP;
				src->state = U_JUMP;
				src->y -= (32) * Settings::CASE_SIZE * (src->loopTime);
			}
			if (src->jumpTmpY + Settings::HIGH_JUMP <= 0)
			{
				src->state = U_END_JUMP;
				src->jumpTmpY = 0;
			}
		}
	if (_referee->colliderCheck(src, Event::I_UP) == 1)
	{
		src->state = U_END_JUMP;
		src->jumpTmpY = 0;
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
	if (src->weapon[0]->fireRateCount <= 0.f)
		{
			src->weapon[0]->fireRateCount = src->weapon[0]->fireRate;
		if (src->weapon[0]->ammo > 0)
			this->_bulletList.push_back(src->weapon[0]->createBullet(src->x + (src->width /2), src->y,0, -1,loopTime));
		}	
	//return;
}

void PhysicEngine::shootDown(AUnit *src)
{
	return;
}

void PhysicEngine::shootLeft(AUnit *src)
{
	if (src->weapon[0]->fireRateCount <= 0.f)
		{
				src->weapon[0]->fireRateCount = src->weapon[0]->fireRate;
			if (src->weapon[0]->ammo > 0)
				this->_bulletList.push_back(src->weapon[0]->createBullet(src->x, src->y + src->height /2,-1, 0,loopTime));
		}
	
	return;
}

void PhysicEngine::shootRight(AUnit *src)
{
	if (src->weapon[0]->fireRateCount <= 0.f)
		{
				src->weapon[0]->fireRateCount = src->weapon[0]->fireRate;
			if (src->weapon[0]->ammo > 0)
				this->_bulletList.push_back(src->weapon[0]->createBullet(src->x + src->width, src->y+ (src->height /2),1, 0,loopTime));
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
	if (src->state == U_JUMP)
		src->state = U_END_JUMP;
	if (_referee->applyGravity(src) == false)
	{
		src->jumpTmpY = 0;
		src->state = U_NORMAL;
		src->act = WALK;
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
		_referee->applyGravity(src);
	}
	else
	{
		src->doubleJump = true;
		src->jumpTmpY = 0;
		src->state = U_NORMAL;
		src->act = WALK;
	}
	return;
}