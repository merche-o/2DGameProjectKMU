#pragma once

#include <vector>
#include "AUnit.h"
#include "Weapon.h"

class Ressources
{
public:
	std::vector<AUnit*> ennemy;
	std::vector<Weapon*> weapon;

private:

public:
	Ressources(void);
	~Ressources(void);

	void loadEnnemiesFromFile(std::string fileName);
	void loadWeaponsFromFile(std::string fileName);
};

