#pragma once

#include "SFML\Graphics.hpp"

enum e_dir
{
	LEFT,
	RIGHT
};

enum e_act
{
	WALK,
	JUMP
};

class AUnit
{
public:
	int x;
	int y;
	int life;
	int shield;
	int speed;
	sf::Texture texture;
	int width;
	int height;
	int animFrame;
	e_dir dir;
	e_act act;
	sf::Time spawm;
	sf::Clock timer;

public:
	AUnit(void);
	~AUnit(void);

	void nextFrame();
};