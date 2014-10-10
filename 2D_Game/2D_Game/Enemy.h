#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"

class Enemy : public AUnit
{
public:
	

private:
enum e_move 
	{
		e_LEFT,
		e_RIGHT,
	};

public:
	Enemy(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile);
	~Enemy(void);
	e_move move_state;
};
