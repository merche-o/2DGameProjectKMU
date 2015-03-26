// Olivier

#include "Enemy.h"


Enemy::Enemy(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, enemy_type type, float &loopTime)
	: AUnit(Life, Speed, Damage, SpawnTime, Texture, X, Y, Dir,  loopTime), etype(type)
{
	particleColor = sf::Color(255, 150, 0);
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

	// ouest
	// nord-ouest
	// nord
	// nord-est
	// est
}