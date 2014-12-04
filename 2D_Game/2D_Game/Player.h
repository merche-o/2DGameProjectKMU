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
	//::vector<Weapon*> weapon;
	std::vector<Bonus*> bonus;
	float inDash;
		float tmpTime;
	Spell spell;
	int numPlayer;

private:

public:
	Player(Ressources & Ress, float &LoopTime, int NumPlayer);
	~Player(void);
	void init(Ressources &);
};

