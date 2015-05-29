
#include "EnemyWave.h"



EnemyWave::EnemyWave(int _length, float _first_AISpawnTime, float _second_AISpawnTime, float _third_AISpawnTime, float _fourth_AISpawnTime)
		: length(_length)
{
	spawnTime.push_back(_first_AISpawnTime);
	spawnTime.push_back(_second_AISpawnTime);
	spawnTime.push_back(_third_AISpawnTime);
	spawnTime.push_back(_fourth_AISpawnTime);
	clock.restart();
}

EnemyWave::~EnemyWave(void)
{
}

