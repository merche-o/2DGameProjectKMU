#pragma once

#include <utility>
#include "SFML\Graphics.hpp"

class Platform
{
public:
	enum platform_type
	{
		DISAPPEAR,
		GO_LEFT,
		GO_RIGHT,
		DAMAGE,
		SLOWING,
		NONE
	};

public:
	float x;
	float y;
	int length;
	platform_type type;
	int speed;
	bool isMorphing;
	int transp;
	std::vector<std::pair<int, int> > pos;
	float activMorph;
	float morphTime;
	float & loopTime; // time of one global loop
	float morph; // additionnal loopTime

private:

public:
	Platform(int X, int Y, int Length, float & Time);
	~Platform(void);

	void checkMorphTime();
	void playMorph(std::vector<Platform*> & platform);
	bool checkDead();
	void refreshTime();
	void resetTime();
};

// Refaire les plateforms sous forme de class = stockage dynamique pour application dynamique
// Check it :
// creer une enum de type de platform, et donner un type a chaque platform
// en fonction de ce type, la plateform va changer differement
// tableau de pointeur sur fonction de type