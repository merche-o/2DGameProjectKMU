#pragma once

#include <vector>
#include "Display.h"
#include "Player.h"
#include "Referee.h"
#include "Event.h"

class IA 
{
private:
	Referee &_ref;
	std::vector<AUnit*> &_ennemyList;
	void fillInputMap(AUnit *);
public:
	void setEnnemiesIM();
	IA(Referee &,  std::vector<AUnit*>  &enemylist);
	~IA(void);


};

