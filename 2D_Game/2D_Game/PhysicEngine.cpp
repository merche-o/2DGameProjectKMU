//Joris

#include "PhysicEngine.h"
#include <iostream>

PhysicEngine::PhysicEngine(std::vector<Player *> &player, std::vector<AUnit*>  &enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList, Map & map, float  &LoopTime, SoundEngine &sound)
: _player(player), _ennemyList(enemylist), _itemList(itemList), _bulletList(bulletList), _map(map), loopTime(LoopTime), _sound(sound)
{
	// actionManager

	actionManager[Event::I_UP] = &PhysicEngine::Jump;
	actionManager[Event::I_DOWN] = &PhysicEngine::moveDown;
	actionManager[Event::I_LEFT] = &PhysicEngine::moveLeft;
	actionManager[Event::I_RIGHT] = &PhysicEngine::moveRight;
	actionManager[Event::I_FIRE_UP] = &PhysicEngine::shootUp;
	actionManager[Event::I_FIRE_DOWN] = &PhysicEngine::shootDown;
	actionManager[Event::I_FIRE_LEFT] = &PhysicEngine::shootLeft;
	actionManager[Event::I_FIRE_RIGHT] = &PhysicEngine::shootRight;
	actionManager[Event::I_BONUS] = &PhysicEngine::useBonus;
	actionManager[Event::I_SWAP] = &PhysicEngine::swapSpell;
	actionManager[Event::I_WEAPON_1] = &PhysicEngine::changeWeapon1;//
	actionManager[Event::I_WEAPON_2] = &PhysicEngine::changeWeapon2;//
	actionManager[Event::I_WEAPON_3] = &PhysicEngine::changeWeapon3;//
	actionManager[Event::I_WEAPON_4] = &PhysicEngine::changeWeapon4;//

	releaseActionManager[Event::I_UP] = &PhysicEngine::RJump;
	releaseActionManager[Event::I_DOWN] = &PhysicEngine::RmoveDown;
	releaseActionManager[Event::I_LEFT] = &PhysicEngine::RmoveLeft;
	releaseActionManager[Event::I_RIGHT] = &PhysicEngine::RmoveRight;
	releaseActionManager[Event::I_FIRE_UP] = &PhysicEngine::RshootUp;
	releaseActionManager[Event::I_FIRE_DOWN] = &PhysicEngine::RshootDown;
	releaseActionManager[Event::I_FIRE_LEFT] = &PhysicEngine::RshootLeft;
	releaseActionManager[Event::I_FIRE_RIGHT] = &PhysicEngine::RshootRight;
	releaseActionManager[Event::I_BONUS] = &PhysicEngine::RuseBonus;
	releaseActionManager[Event::I_SWAP] = &PhysicEngine::RswapSpell;
	releaseActionManager[Event::I_WEAPON_1] = &PhysicEngine::RchangeWeapon1;
	releaseActionManager[Event::I_WEAPON_2] = &PhysicEngine::RchangeWeapon2;
	releaseActionManager[Event::I_WEAPON_3] = &PhysicEngine::RchangeWeapon3;
	releaseActionManager[Event::I_WEAPON_4] = &PhysicEngine::RchangeWeapon4;

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
	collide(this->_player[playerId]);
	_referee->collideSpell(this->_player[playerId]);
	_referee->setPlayerPosition(this->_player);
}

void PhysicEngine::moveLeft(AUnit *src)
{
// 	 if (src->x - (src->speed * src->loopTime) <= -5)
// 		return;
	src->x -= (src->speed * src->loopTime);
	src->nextFrame();
	if (src->isPlayer == false)
		return;
	//if (((Player *)src)->inDash == 0)
	//	((Player *)src)->inDash = 1;
	//if (((Player *)src)->inDash == 2 && ((Player *)src)->tmpTime < 0.2)
	//{
	//	((Player *)src)->inDash = 3;
	//	src->x -= (src->speed * 5 * src->loopTime);
	//}
}

void PhysicEngine::moveRight(AUnit *src)
{
	// Le 5 doit surement etre changer
// 	if (src->x + (src->speed *src->loopTime) >= Settings::WIDTH_GAME + 5 - src->width )
// 		return;
	src->x += (src->speed *src->loopTime);
	src->nextFrame();
	if (src->isPlayer == false)
		return;
	/*if (((Player *)src)->inDash == 0)
	((Player *)src)->inDash = -1;
	if (((Player *)src)->inDash == -2 && ((Player *)src)->tmpTime < 0.2)
	{
	((Player *)src)->inDash = -3;
	src->x += (src->speed * 5 * src->loopTime);
	}*/
}

void PhysicEngine::Jump(AUnit *src)
{
	if (_referee->colliderCheck(src, Event::I_UP) != 1)
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
			_sound.playSound(_sound.sound["jump"], true);
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
	//if (src->isPlayer == true)
	if (((Player *)src)->spell.play == false && ((Player *)src)->spellUsed == false)
	{
		((Player *)src)->spellUsed = true;
		((Player *)src)->spell.launched = true;
		//((Player *)src)->spell.launch();
	}
	return;
}

void PhysicEngine::swapSpell(AUnit *src)
{
	if (((Player *)src)->spell.type == LASER)
	{
		((Player *)src)->spell.updateSpell(EXPLOSION);
	}
	else
		((Player *)src)->spell.updateSpell(LASER);

	return;
}

void PhysicEngine::shootUp(AUnit *src)
{
	if (src->weapon[src->weaponUsed]->fireRateCount <= 0.f)
	{
		src->weapon[src->weaponUsed]->fireRateCount = src->weapon[0]->fireRate;
		if (src->weapon[src->weaponUsed]->ammo > 0)
		{
			_sound.playSound(_sound.sound["shoot"], true);
			this->_bulletList.push_back(src->weapon[src->weaponUsed]->createBullet(src->x + (src->width /2), src->y,0, -1,loopTime));
		}
	}	
}

void PhysicEngine::shootDown(AUnit *src)
{
	return;
}

void PhysicEngine::shootLeft(AUnit *src)
{
	if (src->weapon[src->weaponUsed]->fireRateCount <= 0.f)
	{
		src->weapon[src->weaponUsed]->fireRateCount = src->weapon[src->weaponUsed]->fireRate;
		if (src->weapon[src->weaponUsed]->ammo > 0)
		{
			_sound.playSound(_sound.sound["shoot"], true);
			this->_bulletList.push_back(src->weapon[src->weaponUsed]->createBullet(src->x, src->y + src->height /2,-1, 0,loopTime));
		}
	}
	return;
}

void PhysicEngine::shootRight(AUnit *src)
{
	if (src->weapon[src->weaponUsed]->fireRateCount <= 0.f)
	{
		src->weapon[src->weaponUsed]->fireRateCount = src->weapon[src->weaponUsed]->fireRate;
			if (src->weapon[src->weaponUsed]->ammo > 0)
			{
				_sound.playSound(_sound.sound["shoot"], true);
				this->_bulletList.push_back(src->weapon[src->weaponUsed]->createBullet(src->x + src->width, src->y+ (src->height /2),1, 0,loopTime));
			}
	}
	return;
}

void PhysicEngine::changeWeapon1(AUnit *src)
{
	src->weaponUsed = 0;
}

void PhysicEngine::changeWeapon2(AUnit *src)
{
	src->weaponUsed =  1;
}

void PhysicEngine::changeWeapon3(AUnit *src)
{
	src->weaponUsed = 2;
}

void PhysicEngine::changeWeapon4(AUnit *src)
{
	src->weaponUsed =  3;
}


//Release button

void PhysicEngine::RmoveLeft(AUnit *src)
{
	src->animFrame = 1;
	if (src->isPlayer == false)
		return;

	//For Dash
	//if (((Player *)src)->inDash == 1)
	//{
	//	((Player *)src)->tmpTime = 0;
	//	((Player *)src)->inDash = 2;
	//	((Player *)src)->tmpTime += src->loopTime;
	//}
	//else if (((Player *)src)->inDash == 2)
	//{
	//	((Player *)src)->tmpTime += loopTime;
	//}

	//if (((Player *)src)->inDash > 0 && ((Player *)src)->tmpTime > 0.5)
	//{
	//		
	//	((Player *)src)->inDash = 0;
	//	((Player *)src)->tmpTime = 0;
	//}
	//if (((Player *)src)->inDash == 0)
	//	((Player *)src)->tmpTime = 0;
	//if (((Player *)src)->inDash == 3)
	//	((Player *)src)->tmpTime += src->loopTime;
	//return;
}


void PhysicEngine::RmoveRight(AUnit *src)
{
	src->animFrame = 1;
	if (src->isPlayer == false)
		return;

	//For Dash
	//if (((Player *)src)->inDash == -1)
	//{
	//	((Player *)src)->tmpTime = 0;
	//	((Player *)src)->inDash = -2;
	//	((Player *)src)->tmpTime += src->loopTime;
	//}
	//else if (((Player *)src)->inDash == -2)
	//{
	//	((Player *)src)->tmpTime += loopTime;
	//}
	//if (((Player *)src)->inDash < 0 && ((Player *)src)->tmpTime > 0.5)
	//{
	//	((Player *)src)->inDash = 0;
	//	((Player *)src)->tmpTime = 0;
	//}
	//if (((Player *)src)->inDash == 0)
	//	((Player *)src)->tmpTime = 0;
	//if (((Player *)src)->inDash == -3)
	//	((Player *)src)->tmpTime += src->loopTime;

	return;
}

void PhysicEngine::RJump(AUnit *src)
{
	if (src->isPlayer || (((Enemy *)src)->type == enemyType::E_BASIC && ((Enemy *)src)->type == enemyType::E_JUMPCASE))
	{
		if (src->state == U_JUMP)
			src->state = U_END_JUMP;
		if (_referee->applyGravity(src) == false)
		{
			src->jumpTmpY = 0;
			src->state = U_NORMAL;
			src->act = WALK;
		}
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

void PhysicEngine::RswapSpell(AUnit *src)
{
}

void PhysicEngine::RchangeWeapon1(AUnit *src)
{
}

void PhysicEngine::RchangeWeapon2(AUnit *src)
{
}

void PhysicEngine::RchangeWeapon3(AUnit *src)
{
}

void PhysicEngine::RchangeWeapon4(AUnit *src)
{
}

//Physics

void PhysicEngine::collide(AUnit *src) 
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