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

enum unit_state {
	U_NORMAL,
	U_JUMP,
	U_END_JUMP,
	U_FIRE,
	U_DASH,
	U_HIT,
	U_DEAD,
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
	int damage;
	int spawnTime;
	e_dir dir;
	e_act act;
	unit_state state;
	sf::Time spawm;
	sf::Clock timer;
	std::vector<bool> inputMap;

	//there is probably a best way to do it
	int jumpTmpY;

public:
	AUnit(void);
	AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile);
	~AUnit(void);

	void nextFrame();
	
};
