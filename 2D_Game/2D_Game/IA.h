#pragma once

#include <vector>
#include "Display.h"
#include "Player.h"
#include "Referee.h"
#include "Event.h"
#include "Enemy.h"

class IA 
{
private:
	Referee &_ref;
	std::vector<AUnit*> &_ennemyList;

	void fillInputMap(Enemy  *,float x, float y);
	void basicIA(Enemy *, float x, float y);
	void jumpIA(Enemy *, float x, float y);
	void flyIA(Enemy *, float x, float y);
	void floatIA(Enemy *, float x, float y);
	sf::Vector2f rotateVector(double, sf::Vector2f);
	double	angleBtwVectors(sf::Vector2f, sf::Vector2f);
	sf::Vector2f NormalizeVector(sf::Vector2f);

	std::map<enemyType, void(IA:: *)(Enemy *src, float x, float y)> IAManager;
	int flyHeight;

public:
	void setEnnemiesIM(float x, float y);
	IA(Referee &,  std::vector<AUnit*>  &enemylist);
	~IA(void);
};

