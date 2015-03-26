//Joris & Olivier
#include "IA.h"	

IA::IA(Referee &ref,  std::vector<AUnit*>  &enemylist)
	: _ref(ref), _ennemyList(enemylist)  
{
	this->IAManager[E_BASIC] = &IA::basicIA;
	this->IAManager[E_JUMPCASE] = &IA::jumpIA;
}

IA::~IA(void)
 {
 }

// Use different IA type
void IA::setEnnemiesIM(float x, float y)
{
	int i;
	i = 0;
		
	while (i < _ennemyList.size())
		{
			fillInputMap((Enemy *)_ennemyList[i],x,y);
			++i;
		}
}

void IA::fillInputMap(Enemy *src, float x, float y)
{
	(this->*(IAManager[src->etype]))(src,x,y);
	src->createParticles();
}

void IA::jumpIA(Enemy *src, float x, float y)
{
	src->prevY = src->y;
	src->prevX = src->x;
	int dir = _ref.colliderCheck(src, Event::I_NONE);

	// Si le saut est fini, je relache le bouton saut
	if (src->state == U_END_JUMP)
		src->inputMap[Event::I_UP] = false;

	if (dir == 3 && src->dir == RIGHT)
	{
		src->dir = LEFT;
	}
	else if (dir == 4 && src->dir == LEFT)
	{
		src->dir = RIGHT;
	}

	if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
		return;
	}
	else
	{
		src->fallingSpeed = 10 * Settings::CASE_SIZE;
	}
	
	// Check with Player position to follow him
	if ( y == src->y)
	{
		if (x < src->x)
		{
			src->dir = LEFT;
		}
		else if (x > src->x)
		{
			src->dir = RIGHT;
		}
	}
	// Si le joueur est au dessus de l'ennemi et que ce dernier n'est pas en train de sauter
	if (y < src->y && src->inputMap[Event::I_UP] == false)
	{
		// Si il est possible de sauter sur une plateforme plus haute, l'ia y saute
		if (_ref.IAJumpToPlatform(src))
			src->inputMap[Event::I_UP] = true;
	}

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

void IA::basicIA(Enemy *src, float x, float y)
{
	src->prevY = src->y;
	src->prevX = src->x;
	int dir = _ref.colliderCheck(src, Event::I_NONE);
	
	if (dir == 3 && src->dir == RIGHT)
	{
		src->dir = LEFT;
	}
	else if (dir == 4 && src->dir == LEFT)
	{
			
		src->dir = RIGHT;
	}

	if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
		return;
	}
	else
	{
		src->fallingSpeed = 10 * Settings::CASE_SIZE;
	}
	
	// Check with Player position to follow him
	if ( y == src->y)
	{
		if (x < src->x)
		{
			src->dir = LEFT;
		}
		else if (x > src->x)
		{
			src->dir = RIGHT;
		}
	}

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

void IA::randIA(Enemy *src,float x, float y)
{
	basicIA(src,x,y);
}
