#pragma once

#include <list>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"

class Player : public AUnit
{
private:
	int score;
	std::list<Weapon> weapon;
	std::list<Bonus> bonus;
	std::list<Spell> spell;

public:
	Player(void);
	~Player(void);
};

