#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"

enum enemy_type 
	{
		E_BASIC,
		E_JUMPCASE
	};

enum damageType  	{
		E_JUMP,
		E_BULLET,
		E_BOTH
	};


class Enemy : public AUnit
{
public:
	

private:


public:
	Enemy(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, enemy_type type, float &loopTime);
	~Enemy(void);
	enemy_type etype;
	void getHit(int);
};
