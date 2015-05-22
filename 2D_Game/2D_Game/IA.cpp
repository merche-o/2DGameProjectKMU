//Joris & Olivier
#include "IA.h"	

#include <iostream>

IA::IA(Referee &ref,  std::vector<AUnit*>  &enemylist)
	: _ref(ref), _ennemyList(enemylist), flyHeight(Settings::CASE_SIZE / 2 - 5)  
{
	this->IAManager[E_BASIC] = &IA::basicIA;
	this->IAManager[E_JUMPCASE] = &IA::jumpIA;
	this->IAManager[E_FLY] = &IA::flyIA;
	this->IAManager[E_FLOAT] = &IA::floatIA;
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

sf::Vector2f IA::rotateVector(double angle, sf::Vector2f vector)
{
	sf::Vector2f newVector;

	newVector.x = vector.x * cos(angle) - vector.y * sin(angle);
	newVector.y = vector.x * sin(angle) + vector.y * cos(angle);
	return newVector;
}

double	IA::angleBtwVectors(sf::Vector2f vect1, sf::Vector2f vect2)
{
	double angle;

	angle = acos((vect1.x * vect2.x + vect1.y * vect2.y) / (sqrt(pow(vect1.x, 2) + pow(vect1.y, 2)) * sqrt(pow(vect2.x, 2) + pow(vect2.y, 2))));
	return angle;
}

sf::Vector2f IA::NormalizeVector(sf::Vector2f vector)
{
	double lenght;

	lenght = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	vector.x = vector.x / lenght;
	vector.y = vector.y / lenght;
	return vector;
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
	srand(time(NULL) + src->timer.getElapsedTime().asSeconds());
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
	//if (y == src->y)
	if (rand() % 20 == 5)
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

void IA::floatIA(Enemy *src, float x, float y)
{
	srand(time(NULL) + src->timer.getElapsedTime().asSeconds());
	src->prevY = src->y;
	src->prevX = src->x;
// 	Enemy enemyTemp = *src;
// 
// 	if (! _ref.AICollideWalls(&enemyTemp, flyHeight + 1))
// 		src->currentDirection = src->nextDirection;
	if (src->nextDirection == DOWN && _ref.AICheckDown(src, flyHeight))
		{
			src->currentDirection = DOWN;
			src->nextDirection = FORWARD;
		}
	else if (src->nextDirection == UP && _ref.AICheckUp(src, flyHeight))
	{
		src->currentDirection = UP;
		src->nextDirection = FORWARD;
	}

	if (src->currentDirection == FORWARD)
	{
		if (src->dir == LEFT)
		{
			src->x -= src->loopTime * src->speed;
		}
		else
		{
			src->x += src->loopTime * src->speed;
		}
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

	//std::cout << "x : " << src->x << "   y : " << src->y << std::endl;

	_ref.AICollideScreen(src);
	if (_ref.AICollideWalls(src, flyHeight))
	{
		if (src->currentDirection == DOWN || src->currentDirection == UP)
		{
			src->nextDirection = FORWARD;
		}
		else if (src->y > y + Settings::CASE_SIZE)
		{
			src->nextDirection = UP;
		}
		else
		{
			src->nextDirection = DOWN;
		}

		if (src->currentDirection == DOWN)
		{
			src->currentDirection = FORWARD;
		}
		else if (src->currentDirection == UP)
		{
			src->currentDirection = FORWARD;
		}
		//src->nextDirection = (enemyDirection)(rand() % (int)ENEMYDIRECTION_SIZE);
		
	}
	/*if (rand() % 40 == 1)
		src->nextDirection = (enemyDirection)(rand() % (int)ENEMYDIRECTION_SIZE);*/
	if (rand() % 7 == 2)
	{
		//src->nextDirection = (enemyDirection)(rand() % (int)ENEMYDIRECTION_SIZE);
		if (src->dir == LEFT && src->x + src->width < x)
			src->dir = RIGHT;
		else if (src->dir == RIGHT && src->x > x + Settings::CASE_SIZE)
			src->dir = LEFT;
		if (src->y > y + Settings::CASE_SIZE)
		{
			src->nextDirection = UP;
		}
		else
		{
			src->nextDirection = DOWN;
		}
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

void IA::flyIA(Enemy *src, float x, float y)
{
	src->prevY = src->y;
	src->prevX = src->x;
	double angle;
	sf::Vector2f newVector;

	angle = angleBtwVectors(src->directionVector, sf::Vector2f(x - src->x, y - src->y));
	if (angle < 0.01)
		angle = 0;
	else
	{
		newVector = rotateVector(angle * 0.05, src->directionVector);
		if (angleBtwVectors(newVector, sf::Vector2f(x - src->x, y - src->y)) > angle)
			newVector = rotateVector(-angle * 0.05, src->directionVector);
		src->directionVector = NormalizeVector(newVector);
	}
	src->x += src->directionVector.x * src->speed * src->loopTime * 1;
	src->y += src->directionVector.y * src->speed * src->loopTime * 1;
}