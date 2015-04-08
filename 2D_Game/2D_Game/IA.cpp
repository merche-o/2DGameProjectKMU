//Joris & Olivier
#include "IA.h"	

#include <iostream>

IA::IA(Referee &ref,  std::vector<AUnit*>  &enemylist)
	: _ref(ref), _ennemyList(enemylist), flyHeight(Settings::CASE_SIZE / 2)  
{
	this->IAManager[E_BASIC] = &IA::basicIA;
	this->IAManager[E_JUMPCASE] = &IA::jumpIA;
	this->IAManager[E_FLY] = &IA::flyIA;
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

	if ((dir == 3 && src->dir == RIGHT) || (src->x + src->width >= Settings::WIDTH_GAME - 2 && src->dir == RIGHT))
	{
		src->dir = LEFT;
	}
	else if ((dir == 4 && src->dir == LEFT) || (src->x <= 2 && src->dir == LEFT))
	{
		src->dir = RIGHT;
	}

	if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
		//return;
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


	if ((dir == 3 && src->dir == RIGHT) || (src->x + src->width >= Settings::WIDTH_GAME - 2 && src->dir == RIGHT))
	{
		src->dir = LEFT;
	}
	else if ((dir == 4 && src->dir == LEFT) || (src->x <= 2 && src->dir == LEFT))
	{
			
		src->dir = RIGHT;
	}

	if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
		//return;
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


void IA::flyIA(Enemy *src, float x, float y)
{
	src->prevY = src->y;
	src->prevX = src->x;
// 	Enemy enemyTemp = *src;
// 
// 	if (! _ref.AICollideWalls(&enemyTemp, flyHeight + 1))
// 		src->currentDirection = src->nextDirection;

	if (src->currentDirection == FORWARD)
	{
		if (src->dir == LEFT)
			src->x -= src->loopTime * src->speed;
		else
			src->x += src->loopTime * src->speed;
		src->nextFrame();
	}
	else if(src->currentDirection == UP)
	{
		src->y -= src->loopTime * src->speed;
	}
	else if (src->currentDirection == DOWN)
	{
		src->y += src->loopTime * src->speed;
	}

	_ref.AICollideScreen(src);
	if (_ref.AICollideWalls(src, flyHeight))
	{
		src->nextDirection = (enemyDirection)(rand() % (int)ENEMYDIRECTION_SIZE);
	}


	/*int dir = _ref.colliderCheck(src, Event::I_NONE);*/

	//si le saut est fini, je relache le bouton saut
	/*if (src->state == U_END_JUMP)
		src->inputMap[Event::I_UP] = false;*/

	/*if (dir == 3 && src->dir == RIGHT)
	{
		src->dir = LEFT;
	}
	else if (dir == 4 && src->dir == LEFT)
	{

		src->dir = RIGHT;
	}*/
	/*if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
		return;
	}
	else
	{
		src->fallingSpeed = 10 * Settings::CASE_SIZE;
	}*/
	// Check with Player position to follow him
	/*if ( y == src->y)
	{
		if (x < src->x)
		{
			src->dir = LEFT;
		}
		else if (x > src->x)
		{
			src->dir = RIGHT;
		}
	}*/
	//si le joueur est au dessus de l'ennemi et que ce dernier n'est pas en train de sauter
	/*if (y < src->y && src->inputMap[Event::I_UP] == false)
	{
		//si il est possible de sauter sur une plateforme plus haute, l'ia y saute
		if (_ref.IAJumpToPlatform(src))
			src->inputMap[Event::I_UP] = true;
	}*/

	/*if (src->dir == RIGHT)
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
	}	*/
}
