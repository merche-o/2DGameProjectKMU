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
	std::vector<Bonus*> bonus;
	float inDash;
	float tmpTime;
	Spell spell;
	bool isSpell;
	int numPlayer;
	bool isAlive;

	bool spellUsed;
	sf::Clock timer;
	sf::Time cd;
	float cdTime;

private:

public:
	Player(Ressources & Ress, float &LoopTime, int NumPlayer);
	void changeWeaponLeft();
	void changeWeaponRight();
	void getNewWeapon(int weaponID, Ressources &Ress);
	~Player(void);
	void explode();
	void init(Ressources &);
};

