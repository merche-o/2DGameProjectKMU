#include "IA.h"	

IA::IA(Referee &ref,  std::vector<AUnit*>  &enemylist):_ref(ref), _ennemyList(enemylist)  
{
	
}

IA::~IA(void)
 {
 }

void IA::setEnnemiesIM()
{
	int i;

	i = 0;

	while (i < _ennemyList.size())
		{
			fillInputMap(_ennemyList[i]);
			++i;
		}

}

void IA::fillInputMap(AUnit * src)
{
		
	if (src->dir == RIGHT)
		src->inputMap[Event::I_RIGHT] = true;
	else if (src->dir == LEFT)
		src->inputMap[Event::I_LEFT] = true;
}