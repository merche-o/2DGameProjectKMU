// Joris & Olivier

#include "Referee.h"
#include <iostream>

Referee::Referee(std::vector<AUnit*> & enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList, Map &map, float &LoopTime, Ressources &Res, SoundEngine &sound)
	: _enemyList(enemylist), _itemList(itemList),_bulletList(bulletList), _map(map), loopTime(LoopTime), _res(Res), _sound(sound)
{
	collideManager.push_back(&Referee::collideEnemy);
	collideManager.push_back(&Referee::collideBonus);
	collideManager.push_back(&Referee::collideWall);
	enemiesCount = 0;
}


Referee::~Referee()
{
}

// Function to use all colliders
int Referee::colliderCheck(AUnit  *src, Event::Input const &btn)
{
	int target = -1;
	for (int i = 0; i < 3; ++i)
	{
		if ( (target =(this->*(collideManager[i]))(src, btn)) != -1)
			return (target);
	}
	return (-1);
}

// collide function for all bonus items
int Referee::collideBonus(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_NONE && src->isPlayer == true)
	{
		for (int i = 0; i < this->_itemList.size(); i++)
		{
			bool intersection; // Factorised  algo for collide between 2 rectangles
			if (src->x + src->width < this->_itemList[i]->x ||
				this->_itemList[i]->x + this->_itemList[i]->texture.getSize().x < src->x ||
				src->y + src->height < this->_itemList[i]->y ||
				this->_itemList[i]->y + this->_itemList[i]->texture.getSize().y < src->y)
			{
				intersection = false;
			}
			else
			{
				intersection = true;
				if (_itemList[i]->type == Item::COINS) // Check if it's a coin to increment this value
				((Player *)src)->score += _itemList[i]->score;
					_sound.playSound(_sound.sound["coin"], false);

				if(_itemList[i]->type == Item::AMMO) // Check if it's an ammo to increment this value
				{
					((Player *)src)->weapon[((Player *)src)->weaponUsed]->ammo += 5;
				}
				_itemList.erase(_itemList.begin() + i);
			}
		}
	}
	return (-1);
}

void Referee::AICollideScreen(Enemy * enemy)
{
}

bool Referee::AICheckDown(Enemy * enemy, int flyHeight)
{
	for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (!(	enemy->x + enemy->width					<	_map.platform[i]->x	- flyHeight												||
			enemy->x							>	_map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE + flyHeight 	||
			enemy->y + enemy->height + flyHeight + 5	<	_map.platform[i]->y																||
			enemy->y									>	_map.platform[i]->y + Settings::CASE_SIZE	))
		{
			return false;
		}
	}
	return true;
}

bool Referee::AICheckUp(Enemy * enemy, int flyHeight)
{
	for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (!(	enemy->x + enemy->width	+ flyHeight * 2	<	_map.platform[i]->x														||
			enemy->x - flyHeight * 2					>	_map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE	||
			enemy->y + enemy->height					<	_map.platform[i]->y														||
			enemy->y									>	_map.platform[i]->y + Settings::CASE_SIZE + flyHeight	))
		{
			return false;
		}
	}
	return true;
}

bool Referee::AICollideWalls(Enemy * enemy, int flyHeight)
{
	for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (!(	enemy->x + enemy->width	<	_map.platform[i]->x														||
			enemy->x					>	_map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE	||
			enemy->y + enemy->height	<	_map.platform[i]->y - flyHeight										||
			enemy->y					>	_map.platform[i]->y + Settings::CASE_SIZE))
		{
			if (enemy->currentDirection == FORWARD)
			{
				if (enemy->dir == RIGHT)
				{
					enemy->x = _map.platform[i]->x - enemy->width - 1;
					enemy->dir = LEFT;
				}
				else
				{
					enemy->x = _map.platform[i]->x + Settings::CASE_SIZE * _map.platform[i]->length + 1;
					enemy->dir = RIGHT;
				}
			}
			else if (enemy->currentDirection == UP)
			{
				enemy->y = _map.platform[i]->y + Settings::CASE_SIZE + 1;
				enemy->currentDirection == FORWARD;
			}
			else if (enemy->currentDirection == DOWN)
			{
				enemy->y = _map.platform[i]->y - enemy->height - 1 - flyHeight;
				enemy->currentDirection == FORWARD;
			}
			return true;
		}
	}
	return false;
}


int Referee::collideSpell(AUnit *src)
{
	int k = 0;

	((Player *)src)->cd = ((Player *)src)->timer.getElapsedTime();
	if (((Player *)src)->cd.asSeconds() >= ((Player *)src)->cdTime)
	{
		((Player *)src)->timer.restart();
		((Player *)src)->spellUsed = false;
	}
	if (((Player *)src)->spell.play == true)
	{
		for (int i = 0; i < this->_enemyList.size(); ++i)
		{
			bool intersection;

			if (((Player *)src)->spell.x - ((Player *)src)->spell.scaleX * ((float)((Player *)src)->spell.texture.getSize().x / 2.0) + ((Player *)src)->spell.texture.getSize().x * ((Player *)src)->spell.scaleX < this->_enemyList[i]->x ||
				this->_enemyList[i]->x + this->_enemyList[i]->width < ((Player *)src)->spell.x - ((Player *)src)->spell.scaleX * ((float)((Player *)src)->spell.texture.getSize().x / 2.0) ||
				((Player *)src)->spell.y - ((Player *)src)->spell.scaleY * ((float)((Player *)src)->spell.texture.getSize().y / 2.0) + ((Player *)src)->spell.texture.getSize().y * ((Player *)src)->spell.scaleY < this->_enemyList[i]->y ||
				this->_enemyList[i]->y + this->_enemyList[i]->height < ((Player *)src)->spell.y - ((Player *)src)->spell.scaleY * ((float)((Player *)src)->spell.texture.getSize().y / 2.0))
			{
				intersection = false;
			}
			else
			{
				intersection = true;
				this->_enemyList[i]->getHit(100);
				k += 1;
			}
		}
	}
	return (k);
}

bool Referee::canJump(AUnit *src)
{
	for (int i = 0; i < this->_map.platform.size(); ++i)
		{
			if ((src->x				>	this->_map.platform[i]->x &&
				src->x				<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length) ||
				(src->x + src->width	>	this->_map.platform[i]->x &&
				src->x + src->width	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length))
			{
				if (src->y == this->_map.platform[i]->y + Settings::CASE_SIZE && this->_map.platform[i]->transp > 50)
					return (false);
			}
		}
	return (true);
}

// Check collision with wall
int Referee::collideWall(AUnit *src, Event::Input const &btn)
{
	for (int i = 0; i < this->_map.platform.size(); ++i)
		{
			if (this->_map.platform[i]->transp > 50)
			{
				if (src->state == JUMP)
				{
					if ((src->y				>	this->_map.platform[i]->y &&
						src->y				<	this->_map.platform[i]->y + Settings::CASE_SIZE) ||
						src->y == this->_map.platform[i]->y)
						{
							if (src->state == JUMP)
							{
								if ((src->x				>	this->_map.platform[i]->x &&
									src->x				<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length) ||
									(src->x + src->width	>	this->_map.platform[i]->x &&
									src->x + src->width	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length))
								{
									src->y = this->_map.platform[i]->y + Settings::CASE_SIZE;
									src->state = U_END_JUMP;
									src->jumpTmpY = 0;
									return (1);
								}
							}
						}
				}
				else
				{
					if (src->y == this->_map.platform[i]->y ||
						(src->y		+ src->height		>	this->_map.platform[i]->y &&
						src->y		+ src->height		<	this->_map.platform[i]->y + Settings::CASE_SIZE))
					{
						//// Check with right of player
						if (src->x + src->width	>	this->_map.platform[i]->x  &&
								src->x + src->width	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
						{
							src->x = this->_map.platform[i]->x - src->width;
							return (2);
						}
						// Check with left of player
						else if (src->x			<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
								src->x			>	this->_map.platform[i]->x)
						{
							src->x = this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length;
							return (3);
						}
					}
				}
			}
		}
	return (-1);
}


// Collision with enemies
int Referee::collideEnemy(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_NONE && src->isPlayer == true)
	{
		for (int i = 0; i < this->_enemyList.size(); ++i)
		{
			bool intersection;
			if (	src->x + src->width < this->_enemyList[i]->x || this->_enemyList[i]->x + this->_enemyList[i]->width < src->x 
				||	src->y + src->height < this->_enemyList[i]->y || this->_enemyList[i]->y + this->_enemyList[i]->height < src->y)
			{
				intersection = false;
			}
			else
			{
				intersection = true;
				if (src->y > src->prevY)
				{
					this->_enemyList[i]->getHit(10);
					return (-1);
				}
				return (2);
			}
		}
	}
	return (-1);
}


// Function to apply gravity
bool Referee::applyGravity(AUnit  *src)
{
	for (int i = 0; i < this->_map.platform.size(); ++i)
	{
		if (src->y + src->height	>=	this->_map.platform[i]->y &&
			src->y + src->height	<	this->_map.platform[i]->y + Settings::CASE_SIZE && this->_map.platform[i]->transp > 50)
		{
			if ((src->x		>	this->_map.platform[i]->x  &&
				src->x		<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length) ||
				(src->x + src->width	>	this->_map.platform[i]->x  &&
				src->x + src->width	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length))
			{				
				src->y = this->_map.platform[i]->y - src->height;
				if (this->_map.platform[i]->isMorphing == true)
				{
					if (this->_map.platform[i]->type == Platform::GO_LEFT)
						src->x -= this->_map.platform[i]->speed * loopTime;
					if (this->_map.platform[i]->type == Platform::GO_RIGHT)
						src->x += this->_map.platform[i]->speed * loopTime;
				}
				return (false);
			}
		}
	}
	return (true);
}


// Erase an enemy of the enemylist if he is dead
void Referee::cleanEnemyList()
{
	for (int i = 0; i < this->_enemyList.size(); ++i)
	{
		if (this->_enemyList[i]->l_state == DEAD)
		{
			this->dropCoins((Enemy *)_enemyList[i]);
			this->_enemyList.erase(_enemyList.begin() + i);
			enemiesCount += 1;
		}
	}
}


void Referee::cleanItemList()
{
	for (int i = 0; i < this->_itemList.size(); i++)
	{
		this->_itemList[i]->timeSpawn += loopTime;
		if (this->_itemList[i]->lifeTime <  this->_itemList[i]->timeSpawn)
		{
			this->_itemList.erase(_itemList.begin() + i);
		}
	}
}

int Referee::notInsideWall(int x, int y)
{
	for (int i = 0; i < _map.platform.size(); ++i)
	{
		if (y >= _map.platform[i]->y && y <= _map.platform[i]->y + Settings::CASE_SIZE &&
			x >= _map.platform[i]->x && x <= _map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE)
			return (notInsideWall(x, y - 32));
	}
	return (y);
}

//when an enemy dies, he drops a coin
void Referee::dropCoins(Enemy *src)
{
	int nb_coin = (src->coins / 10);
	
	for (int i = 0; i < nb_coin; ++i)
	{
		float xx = 0;
		float yy = 0;
		if (nb_coin > 1)
		{
			srand(loopTime * (i + nb_coin) * time(NULL));
			xx = rand() % src->width;
			yy = rand() % src->height;
		}
		this->_itemList.push_back(new Coin(src->x + xx, notInsideWall(src->x + xx, src->y + yy), loopTime , (src->coins / nb_coin), Item::COINS, _res.texture["coin"]));
	}
}

// when player is hit, he is invincible
void Referee::playerInvinsibility(Player *player)
{
	if (player->l_state == HIT)
	{
		player->invTime += player->loopTime;
	}
	if(player->invTime >= 1)
	{
		player->l_state = IN_LIFE;
		player->invTime = 0;
	}
}

void Referee::setPlayerPosition(std::vector<Player *> &_player)
{
	for (int i = 0; i < _player.size(); ++i)
	{
		if (_player[i]->y > Settings::HEIGHT_GAME + _player[i]->height)
			_player[i]->y = 0;
		else if (_player[i]->y < 1)
			_player[i]->y  = Settings::HEIGHT_GAME - 2* _player[i]->height;

		if (_player[i]->x > Settings::WIDTH_GAME - 8)
			_player[i]->x = 0;
		else if (_player[i]->x + _player[i]->width < 8)
			_player[i]->x = Settings::WIDTH_GAME - _player[i]->width;
	}
	for (int i = 0; i < _enemyList.size(); ++i)
	{
		if (_enemyList[i]->y > Settings::HEIGHT_GAME + _enemyList[i]->height)
			_enemyList[i]->y = 0;
		else if (_enemyList[i]->y < 1)
			_enemyList[i]->y  = Settings::HEIGHT_GAME - 2* _enemyList[i]->height;

		if (_enemyList[i]->x > Settings::WIDTH_GAME - 8)
			_enemyList[i]->x = 0;
		else if (_enemyList[i]->x + _enemyList[i]->width < 8)
			_enemyList[i]->x = Settings::WIDTH_GAME - _enemyList[i]->width;
	}
}

bool Referee::dealDamage(std::vector<Player *> &_player)
{
	for (int i = 0; i < _player.size(); ++i)
	{
		playerInvinsibility(_player[i]);
		if (collideEnemy(_player[i], Event::I_NONE) == 2)
		{
			_player[i]->getHit(1);
			if (_player[i]->l_state == HIT)
				_sound.playSound(_sound.sound["hurt"], true);
		}
	}
	int c = 0;
	for (int i = 0; i < _player.size(); ++i)
	{
		if (_player[i]->life <= 0)
			c++;
	}
	if (c == _player.size())
		return (false);
	return (true);
}

void Referee::moveBullet(std::vector<Player *> &_player)
{
	for (int i = 0; i < this->_bulletList.size(); i++)
	{
		this->_bulletList[i]->prevX = this->_bulletList[i]->x;
		this->_bulletList[i]->prevY = this->_bulletList[i]->y;

		this->_bulletList[i]->x += this->_bulletList[i]->dirX *  this->_bulletList[i]->speed * (this->loopTime);
		this->_bulletList[i]->y += this->_bulletList[i]->dirY * this->_bulletList[i]->speed * (this->loopTime);
		if(this->_bulletList[i]->destroy() == true)
			this->_bulletList.erase(this->_bulletList.begin() + i);
		else
		{
			for (int i2 = 0; i2 < this->_map.platform.size(); i2++)
			{
				if (this->_bulletList[i]->x	<= this->_map.platform[i2]->x + (this->_map.platform[i2]->length * Settings::CASE_SIZE) && this->_bulletList[i]->x > this->_map.platform[i2]->x
					&& this->_bulletList[i]->y >= this->_map.platform[i2]->y && this->_bulletList[i]->y <= this->_map.platform[i2]->y + Settings::CASE_SIZE)
					this->_bulletList.erase(this->_bulletList.begin() + i);
			}
		}
	}
	this->bulletHit(_player);

	return;
}

void Referee::bulletHit(std::vector<Player *> &_player)
{				   
	for (int i = 0; i < this->_bulletList.size(); i++)
	{
		for (int i2 = 0; i2 < this->_enemyList.size(); i2++)
		{
			bool intersection = true;

			if (this->_bulletList[i]->dirY == 0)
			{
				if (this->_bulletList[i]->dirX == -1)
				{
					if (this->_enemyList[i2]->x  + this->_enemyList[i2]->width < this->_bulletList[i]->x ||
						this->_bulletList[i]->prevX + this->_bulletList[i]->texture.getSize().x < this->_enemyList[i2]->x ||
						this->_enemyList[i2]->y  + this->_enemyList[i2]->height < this->_bulletList[i]->y ||
						this->_bulletList[i]->y + this->_bulletList[i]->texture.getSize().y < this->_enemyList[i2]->y)
					intersection = false;
				}
				else if (this->_bulletList[i]->dirX == 1)
				{
					if (this->_enemyList[i2]->x  + this->_enemyList[i2]->width < this->_bulletList[i]->prevX ||
						this->_bulletList[i]->x + this->_bulletList[i]->texture.getSize().x < this->_enemyList[i2]->x ||
						this->_enemyList[i2]->y  + this->_enemyList[i2]->height < this->_bulletList[i]->prevY ||
						this->_bulletList[i]->prevY + this->_bulletList[i]->texture.getSize().y < this->_enemyList[i2]->y)
					intersection = false;
				}
			}
			else if (this->_bulletList[i]->dirX == 0)
			{
				if (this->_bulletList[i]->dirY == -1)
				{
					if (this->_enemyList[i2]->x  + this->_enemyList[i2]->width < this->_bulletList[i]->x ||
						this->_bulletList[i]->prevX + this->_bulletList[i]->texture.getSize().x < this->_enemyList[i2]->x ||
						this->_enemyList[i2]->y  + this->_enemyList[i2]->height < this->_bulletList[i]->y ||
						this->_bulletList[i]->prevY + this->_bulletList[i]->texture.getSize().y < this->_enemyList[i2]->y)
					intersection = false;
				}
			}
			if (intersection == true)
			{
				_sound.playSound(_sound.sound["hit"], true);
				this->_enemyList[i2]->getHit(this->_bulletList[i]->damage);
				this->_bulletList.erase(this->_bulletList.begin() + i);
				return;
			}
		}
	}
	return;		   
}
bool Referee::IAJumpToPlatform(AUnit *src)
{
	for (int i = 0; i < _map.platform.size(); ++i)
	{
		if (src->dir == RIGHT)
		{
			if (((src->x > _map.platform[i]->x - Settings::CASE_SIZE * 2) && (src->x < _map.platform[i]->x - Settings::CASE_SIZE * 1)) &&
				((_map.platform[i]->y >= src->y - Settings::CASE_SIZE * 5) && (_map.platform[i]->y < src->y + Settings::CASE_SIZE)))
			{
				return (true);
			}
		}
		else
		{
			if (((src->x < _map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE + Settings::CASE_SIZE * 1) && (src->x > _map.platform[i]->x + _map.platform[i]->length * Settings::CASE_SIZE + Settings::CASE_SIZE * 0)) &&
				((_map.platform[i]->y >= src->y - Settings::CASE_SIZE * 5) && (_map.platform[i]->y < src->y + Settings::CASE_SIZE)))
			{
				return (true);
			}
		}
	}
	return (false);
}