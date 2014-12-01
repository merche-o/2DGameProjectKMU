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
	void fillInputMap(Enemy  *);
	void basicIA(Enemy *);
	void randIA(Enemy *src);
	std::map<enemy_type, void(IA:: *)(Enemy *src)> IAManager;

public:
	void setEnnemiesIM();
	IA(Referee &,  std::vector<AUnit*>  &enemylist);
	~IA(void);
};

