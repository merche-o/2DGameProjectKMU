#include "IA.h"	

IA::IA(Referee &ref,  std::vector<AUnit*>  &enemylist):_ref(ref), _ennemyList(enemylist)  
{
	this->IAManager[E_BASIC] = &IA::basicIA;
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
			fillInputMap((Enemy *)_ennemyList[i]);
			++i;
		}

}

void IA::fillInputMap(Enemy *src)
{
	(this->*(IAManager[src->etype]))(src);		
}

void IA::basicIA(Enemy *src)
{
if (_ref.applyGravity(src) == true)
		return;
	if (_ref.colliderCheck(src, Event::I_RIGHT) == 1 && src->dir == RIGHT)
		src->dir = LEFT;
	else if (_ref.colliderCheck(src, Event::I_LEFT) == 1 && src->dir == LEFT)
		 src->dir = RIGHT;
	
	
	if (src->dir == RIGHT)
	{
	 src->inputMap[Event::I_LEFT] = false;
	 src->inputMap[Event::I_RIGHT] = true;
	 src->nextFrame();
	 }
	else if (src->dir == LEFT)
	{
	 src->inputMap[Event::I_LEFT] = true;
	 src->inputMap[Event::I_RIGHT] = false;
	 src->nextFrame();
	 }	
}
