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
	int damage;
	int width;
	int height;
	int animFrame;
	e_dir dir;
	e_act act;
	sf::Time spawm;
	sf::Clock timer;
	sf::Texture texture;

public:
	AUnit(void);
	AUnit(int life, int speed, int damage, int spawnTime, std::string textureFile);
	~AUnit(void);

	void nextFrame();
};