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
	void randIA(Enemy *src, float x, float y);
	std::map<enemy_type, void(IA:: *)(Enemy *src, float x, float y)> IAManager;

public:
	void setEnnemiesIM(float x, float y);
	IA(Referee &,  std::vector<AUnit*>  &enemylist);
	~IA(void);
};

