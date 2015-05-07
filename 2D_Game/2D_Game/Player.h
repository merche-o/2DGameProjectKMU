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
	bool isSpell;
	int numPlayer;

	// For spell limitation ----> put it on the spell class, cd per spells
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
	void init(Ressources &);
};

