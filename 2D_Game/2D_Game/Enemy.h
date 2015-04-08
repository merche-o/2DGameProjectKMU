#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"

enum enemyDirection
{
	UP,
	DOWN,
	FORWARD,
	ENEMYDIRECTION_SIZE
};

enum enemyType
{
	E_BASIC,
	E_FLY,
	E_JUMPCASE,
	ENEMYTYPE_SIZE
};

enum damageType
{
	E_JUMP,
	E_BULLET,
	E_BOTH
};


class Enemy : public AUnit
{
public:
	enemyType etype;	

private:

public:
	Enemy(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, enemyType type, float &loopTime);
	~Enemy(void);
	enemyType type;
	enemyDirection currentDirection;
	enemyDirection nextDirection;
	void getHit(int);
	void explode();
};
