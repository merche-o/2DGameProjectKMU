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

	void fillInputMap(Enemy  *,Player *);
	void basicIA(Enemy *, Player *);
	void jumpIA(Enemy *, Player *);
	void flyIA(Enemy *, Player *);
	void floatIA(Enemy *, Player *);
	sf::Vector2f rotateVector(double, sf::Vector2f);
	double	angleBtwVectors(sf::Vector2f, sf::Vector2f);
	sf::Vector2f NormalizeVector(sf::Vector2f);

	std::map<enemyType, void(IA:: *)(Enemy *src, Player *)> IAManager;
	int flyHeight;

public:
	void setEnnemiesIM(Player *);
	IA(Referee &,  std::vector<AUnit*>  &enemylist);
	~IA(void);
};

