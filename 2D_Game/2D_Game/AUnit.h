#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include "Weapon.h"
#include "Particle.h"


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

enum unit_state
{
	U_NORMAL,
	U_JUMP,
	U_END_JUMP,
	U_FIRE,
	U_DASH,
	U_HIT,
	U_DEAD
};

enum life_state
{
	IN_LIFE,
	HIT,
	DEAD
};

class AUnit
{
public:
	float x;
	float y;
	int life;
	int shield;
	int speed;
	sf::Texture texture;
	int width;
	int height;
	int animFrame;
	int damage;
	int spawnTime;
	float fallingSpeed;
	float &loopTime;
	float fireRate;
	float timeDone;
	int weaponUsed;
	int numWeapon;
	e_dir dir;
	e_act act;
	life_state l_state;
	unit_state state;
	sf::Time spawn;
	sf::Clock timer;
	std::vector<bool> inputMap;
	float fireRateCount;
	std::vector<Weapon*> weapon;

	//there is probably a best way to do it
	int jumpTmpY;
	bool doubleJump;
	float prevX;
	float prevY;
	bool isPlayer;

	std::vector<Particle*> particles;
	std::vector<Particle*> explosionList;
	sf::Color particleColor;
	float generateParticle;

private:
	
public:
	AUnit(float &);
	AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile, float &loopTime);
	AUnit(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, float &loopTime);
	 virtual void getHit(int dam);
	~AUnit(void);

	void nextFrame();
	void updateClock();
	void createParticles();
};
