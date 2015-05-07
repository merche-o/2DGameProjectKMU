#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"
#include "Settings.h"
#include <cmath>

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
	E_JUMPCASE,
	E_FLOAT,
	E_FLY,
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
	int coins;
	sf::Vector2f directionVector;

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
