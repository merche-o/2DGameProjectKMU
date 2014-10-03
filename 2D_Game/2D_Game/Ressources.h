#pragma once

#include <vector>
#include <map>
#include <SFML\Graphics.hpp>
#include "AUnit.h"
#include "Weapon.h"

class Ressources
{
public:
	std::vector<AUnit*> ennemy;
	std::vector<Weapon*> weapon;
	std::map<std::string, sf::Texture> texture;

private:

public:
	Ressources(void);
	~Ressources(void);

	void loadEnnemiesFromFile(std::string fileName);
	void loadWeaponsFromFile(std::string fileName);
	void loadTexturesFromFile(std::string fileName);
};

