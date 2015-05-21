#pragma once

#include "Ressources.h"
#include "Settings.h"
#include <vector>

class EnemyWave
{
public:
	int length;
	std::vector<float> spawnTime;
	sf::Clock clock;
	

public:
	EnemyWave(int, float, float, float, float);
	~EnemyWave(void);
};

