// Olivier

#include "Enemy.h"

Enemy::Enemy(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, enemyType type, float &loopTime)
	: AUnit(Life, Speed, Damage, SpawnTime, Texture, X, Y, Dir,  loopTime), etype(type), currentDirection(FORWARD), nextDirection(FORWARD)
{
	// Mettre les coins dans le txt Ennemies, recupere dans ressources
	if (etype == E_BASIC)
	{
		particleColor = sf::Color(255, 150, 0);
		coins = 10;
	}
	else if (etype == E_JUMPCASE)
	{
		particleColor = sf::Color(0, 200, 255);
		coins = 20;
	}
	directionVector.x = (Settings::WIDTH_GAME / 2 - x) / sqrt(pow(Settings::WIDTH_GAME / 2 - x, 2) + pow(Settings::HEIGHT_GAME / 2 - y, 2));
	directionVector.y = (Settings::HEIGHT_GAME / 2 - y) / sqrt(pow(Settings::WIDTH_GAME / 2 - x, 2) + pow(Settings::HEIGHT_GAME / 2 - y, 2));
}


Enemy::~Enemy(void)
{
}

void Enemy::getHit(int dam)
{
	if (this->life > 0)
	{
		this->l_state = HIT;
		this->life -= dam;
	}
	if (this->life <= 0)
	{
		this->life = 0;
		this->l_state = DEAD;
	}
}

void Enemy::explode()
{
	// Create Particles in explosionList

	sf::Color col(255, 255, 0);
	// ouest
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, -2, 0, 2, loopTime));
	// nord-ouest
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, -1, -1, 2, loopTime));
	// nord
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 0, -2, 2, loopTime));
	// nord-est
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 1, -1, 2, loopTime));
	// est
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 2, 0, 2, loopTime));
}