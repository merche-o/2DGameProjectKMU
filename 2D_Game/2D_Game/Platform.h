#pragma once

#include <utility>
#include "SFML\Graphics.hpp"

class Platform
{
public:
	enum platform_type
	{
		DISAPPEAR,
		FALLING,
		NONE
	};

public:
	int x;
	int y;
	int length;
	platform_type type;
	bool isMorphing;
	int transp;
	std::vector<std::pair<int, int> > pos;
	int activMorph;
	int morphTime;
	sf::Time morph;
	sf::Clock timer;

private:

public:
	Platform(int X, int Y, int Length);
	~Platform(void);

	void checkMorphTime();
	void playMorph();
	bool checkDead();
};

// Refaire les plateforms sous forme de class = stockage dynamique pour application dynamique
// Check it :
// creer une enum de type de platform, et donner un type a chaque platform
// en fonction de ce type, la plateform va changer differement
// tableau de pointeur sur fonction de type