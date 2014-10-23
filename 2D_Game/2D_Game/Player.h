#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Spell.h"
#include "Ressources.h"

class Player : public AUnit
{
public:
	int score;
	float invTime;
	std::vector<Weapon*> weapon;
	std::vector<Bonus*> bonus;
	std::vector<Spell*> spell;
private:

public:
	Player(Ressources & Ress, float &LoopTime);
	~Player(void);
};

