#pragma once

#include <utility>
#include "SFML\Graphics.hpp"
#include "Ressources.h"

class Platform
{
public:
	enum platform_type
	{
		DISAPPEAR,
		APPEARING,
		GO_LEFT,
		GO_RIGHT,
		GO_UP,
		GO_DOWN,
		DAMAGE,
		SLOWING,
		MAIN,
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
	std::vector<sf::Texture> texture;
	float activMorph;
	float morphTime;
	float morph; // Additionnal loopTime
	float & loopTime;
	Ressources & ress;

	std::vector<int> transpGradient;
	std::vector<float> lifeGradient;

private:

public:
	Platform(int X, int Y, int Length, float & Time, Ressources & r, unsigned int randomize, bool rebuild = false);
	~Platform(void);

	void checkMorphTime();
	void playMorph(std::vector<Platform*> & platform);
	bool checkDead();
	void refreshTime();
	void resetTime();
	void recycle();
	void setNewEvent();
	void isCollidingWithPlatform(std::vector<Platform*> & platform);
};