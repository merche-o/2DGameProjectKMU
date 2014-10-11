#include "Enemy.h"


Enemy::Enemy(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, enemy_type type) : AUnit( Life, Speed,  Damage,  SpawnTime,  Texture,  X,  Y, Dir), etype(type)
{
		
}


Enemy::~Enemy(void)
{
}
