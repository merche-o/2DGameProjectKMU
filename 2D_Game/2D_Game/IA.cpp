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
void IA::setEnnemiesIM(Player * player)
{
	int i;
	i = 0;
		
	while (i < _ennemyList.size())
		{
			fillInputMap((Enemy *)_ennemyList[i], player);
			++i;
		}
}

void IA::fillInputMap(Enemy *src, Player * player)
{
	(this->*(IAManager[src->etype]))(src, player);
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

void IA::jumpIA(Enemy *src, Player * player)
{
	src->prevY = src->y;
	src->prevX = src->x;
	int dir = _ref.colliderCheck(src, Event::I_NONE);

	// Si le saut est fini, je relache le bouton saut
	if (src->state == U_END_JUMP)
	{
		src->inputMap[Event::I_UP] = false;
		src->state = U_NORMAL;
	}

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
	}
	else
	{
		src->fallingSpeed = 10 * Settings::CASE_SIZE;
	}

	// Check with Player position to follow him
	if ( player->y == src->y)
	{
		if (player->x < src->x)
		{
			src->dir = LEFT;
		}
		else if (player->x > src->x)
		{
			src->dir = RIGHT;
		}
	}
	// Si le joueur est au dessus de l'ennemi et que ce dernier n'est pas en train de sauter
	if (src->inputMap[Event::I_UP] == false && player->state == unit_state::U_NORMAL && src->state == unit_state::U_NORMAL)
	{
		// Si il est possible de sauter sur une plateforme plus haute, l'ia y saute
		if (_ref.IAJumpToPlatform(src, player->y < src->y))
			src->inputMap[Event::I_UP] = true;
	}

	if (src->dir == RIGHT)
	{
		src->inputMap[Event::I_LEFT] = false;
		src->inputMap[Event::I_RIGHT] = true;
	}
	else if (src->dir == LEFT)
	{
		src->inputMap[Event::I_LEFT] = true;
		src->inputMap[Event::I_RIGHT] = false;
	}
}

void IA::basicIA(Enemy *src, Player * player)
{
	srand(time(NULL) + src->timer.getElapsedTime().asSeconds() + (unsigned int)src + src->x + src->y);
	src->prevY = src->y;
	src->prevX = src->x;
	int dir = _ref.colliderCheck(src, Event::I_NONE);


	if ((dir == 2 && src->dir == RIGHT))
	{
		src->dir = LEFT;
	}
	else if ((dir == 3 && src->dir == LEFT))
	{
			
		src->dir = RIGHT;
	}

	if (_ref.applyGravity(src) == true)
	{
		src->y += (src->fallingSpeed * (src->loopTime));
		_ref.applyGravity(src);
	}
	else
	{
		src->fallingSpeed = 10 * Settings::CASE_SIZE;
	}
	
	// Check with Player position to follow him
	if (rand() % 20 == 5)
	{
		if (player->x < src->x)
		{
			src->dir = LEFT;
		}
		else if (player->x > src->x)
		{
			src->dir = RIGHT;
		}
	}

	if (src->dir == RIGHT)
	{
		src->inputMap[Event::I_LEFT] = false;
		src->inputMap[Event::I_RIGHT] = true;
	 }
	else if (src->dir == LEFT)
	{
		src->inputMap[Event::I_LEFT] = true;
		src->inputMap[Event::I_RIGHT] = false;
	 }	
}

void IA::floatIA(Enemy *src, Player * player)
{
	srand(time(NULL) + src->timer.getElapsedTime().asSeconds()  + (unsigned int)src + src->x + src->y);
	src->prevY = src->y;
	src->prevX = src->x;

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
		if (src->currentDirection == DOWN || src->currentDirection == UP)
		{
			src->nextDirection = FORWARD;
		}
		else if (src->y > player->y + Settings::CASE_SIZE)
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
	}

	if (rand() % 30 == 2)
	{
		if (src->dir == LEFT && src->x + src->width < player->x)
			src->dir = RIGHT;
		else if (src->dir == RIGHT && src->x > player->x + Settings::CASE_SIZE)
			src->dir = LEFT;
		if (player->state == unit_state::U_NORMAL)
		{
			if (src->y > player->y + Settings::CASE_SIZE)
			{
				src->nextDirection = UP;
			}
			else if (src->y + Settings::CASE_SIZE < player->y)
			{
				src->nextDirection = DOWN;
			}
		}
		if (rand() % 2 == 1 && (src->currentDirection == UP || src->currentDirection == DOWN) && (src->x < Settings::CASE_SIZE || src->x > Settings::WIDTH_GAME - Settings::CASE_SIZE))
		{
			src->currentDirection = FORWARD;
			src->nextDirection = FORWARD;
		}
	}
}

void IA::flyIA(Enemy *src, Player * player)
{
	srand(time(NULL) + src->timer.getElapsedTime().asSeconds()  + (unsigned int)src + src->x + src->y);
	src->prevY = src->y;
	src->prevX = src->x;
	double angle;
	sf::Vector2f newVector;

	angle = angleBtwVectors(src->directionVector, sf::Vector2f(player->x - src->x, player->y - src->y));
	if (angle < 0.01)
		angle = 0;
	else
	{
		newVector = rotateVector(angle * 0.05, src->directionVector);
		if (angleBtwVectors(newVector, sf::Vector2f(player->x - src->x, player->y - src->y)) > angle)
			newVector = rotateVector(-angle * 0.05, src->directionVector);
		src->directionVector = NormalizeVector(newVector);
	}
	src->x += src->directionVector.x * src->speed * src->loopTime * 1;
	src->y += src->directionVector.y * src->speed * src->loopTime * 1;
}