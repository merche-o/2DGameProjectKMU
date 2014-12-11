#include "Referee.h"


Referee::Referee(std::vector<AUnit*> & enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList ,Map &map, float &LoopTime, Ressources &Res) 
: _enemyList(enemylist), _itemList(itemList),_bulletList(bulletList), _map(map), loopTime(LoopTime), _res(Res)
{
	collideManager.push_back(&Referee::collideEnemy);
	collideManager.push_back(&Referee::collideBonus);
	collideManager.push_back(&Referee::collideWall);
	_res.texture["coin"].loadFromFile("../Ressources/Images/ShieldBar.png");
	_res.texture["ammo"].loadFromFile("../Ressources/Images/Ammo0.png");
}


Referee::~Referee()
{
}

int Referee::colliderCheck(AUnit  *src, Event::Input const &btn)
{
	int i = 0;
	int target = -1;
	while (i < 3)
	{
		if ( (target =(this->*(collideManager[i]))(src,btn)) != -1)
			return target;
		++i;
	}
	return -1;
}

int 	Referee::collideBonus(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_NONE && src->isPlayer == true)
	{
		for (int i = 0; i < this->_itemList.size(); i++)
		{
			bool intersection;
			if (src->x + Settings::CASE_SIZE < this->_itemList[i]->x || this->_itemList[i]->x < src->x
			||  src->y + Settings::CASE_SIZE < this->_itemList[i]->y || this->_itemList[i]->y < src->y)
		{
			intersection = false;
		}
			else
			{
				intersection = true;
				if (_itemList[i]->type == Item::COINS)
				((Player *)src)->score += _itemList[i]->score;
			if(_itemList[i]->type == Item::AMMO)
				{
					int i2 = 0;
					while (i2 < ((Player*)src)->weapon.size())
						{
							if (((Player*)src)->weapon[i2]->type == ((Ammo *)(_itemList[i]))->weaponType)
							((Player *)src)->weapon[i2]->ammo += 10;
								i2++;	
						}
				}
			_itemList.erase(_itemList.begin() + i);
			return 5;
			}
		}
	}
	return -1;
}

int Referee::collideWall(AUnit  *src, Event::Input const &btn)
{
	for (int i = 0; i < this->_map.platform.size(); i++)
		{
			if ((src->y				>=	this->_map.platform[i]->y &&
				src->y				<=	this->_map.platform[i]->y + Settings::CASE_SIZE) ||
				(src->y		+Settings::CASE_SIZE		>	this->_map.platform[i]->y &&
				src->y		+Settings::CASE_SIZE		<	this->_map.platform[i]->y + Settings::CASE_SIZE))
				{
					if (btn == Event::I_UP)
						{
							if (src->x				>	this->_map.platform[i]->x &&
								src->x				<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
							{
								src->y = this->_map.platform[i]->y + Settings::CASE_SIZE + 1;
								return 1;
							}
							else if (src->x + Settings::CASE_SIZE	>	this->_map.platform[i]->x &&
									 src->x + Settings::CASE_SIZE	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
							{				
								src->y = this->_map.platform[i]->y + Settings::CASE_SIZE + 1;
								return 1;
							}
						}
					/*if (btn == Event::I_RIGHT)
						{*/
					else if (src->x + Settings::CASE_SIZE	>	this->_map.platform[i]->x  &&
							src->x + Settings::CASE_SIZE	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
							{				
								src->x = this->_map.platform[i]->x - Settings::CASE_SIZE - 1;
								return 3;
							}
						//}
					/*if (btn == Event::I_LEFT)
						{*/
					else if (src->x			<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
							src->x			>	this->_map.platform[i]->x)
							{		
								src->x = this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length + 1;
								return 4;
							}
						//}
				}
		}	
	return -1;
}

int Referee::collideEnemy(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_NONE && src->isPlayer == true)
	{
		for (int i = 0; i < this->_enemyList.size(); i++)
		{
			bool intersection;
			if (	src->x + Settings::CASE_SIZE < this->_enemyList[i]->x || this->_enemyList[i]->x + Settings::CASE_SIZE < src->x 
				||	src->y + Settings::CASE_SIZE < this->_enemyList[i]->y || this->_enemyList[i]->y + Settings::CASE_SIZE < src->y)
			{
				intersection = false;
			}
			else
				{
					intersection = true;
					if (src->y > src->prevY)
					{
						this->_enemyList[i]->getHit(10);
						return -1;
					}
				return 2;
				}
		}
	}
	return -1;
}

bool  Referee::applyGravity(AUnit  *src)
{
for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (src->y + Settings::CASE_SIZE	>=	this->_map.platform[i]->y &&
			src->y + Settings::CASE_SIZE	<	this->_map.platform[i]->y + Settings::CASE_SIZE)
		{
			if (src->x							>=	this->_map.platform[i]->x  &&
				src->x							<=	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
			{				
				src->y = this->_map.platform[i]->y - Settings::CASE_SIZE;
		//		// Fais bouger avec la platform si cette derniere bouge
		//if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_LEFT)
		//	src->x -= (this->_map.platform[i]->speed * src->loopTime);
		//else if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_RIGHT)
		//	src->x += (this->_map.platform[i]->speed * src->loopTime);

				return false;
			}
			else if (src->x + Settings::CASE_SIZE	>=	this->_map.platform[i]->x  &&
					src->x + Settings::CASE_SIZE	<=	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length)
			{
				src->y = this->_map.platform[i]->y - Settings::CASE_SIZE;

		//		// Fais bouger avec la platform si cette derniere bouge
		//if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_LEFT)
		//	src->x -= (this->_map.platform[i]->speed * src->loopTime);
		//else if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_RIGHT)
		//	src->x += (this->_map.platform[i]->speed * src->loopTime);

				return false;
			}
		}
	}
	return true;
}

void Referee::cleanEnemyList()
{
	for (int i = 0; i < this->_enemyList.size(); i++)
	{
		if (this->_enemyList[i]->y > Settings::HEIGHT  || this->_enemyList[i]->l_state == DEAD)
			{
		if (this->_enemyList[i]->l_state == DEAD)
				this->dropCoins((Enemy *)_enemyList[i]);
			this->_enemyList.erase(_enemyList.begin() + i);
			}
	}
}

void Referee::cleanItemList(){
	for (int i = 0; i < this->_itemList.size(); i++)
	{
		this->_itemList[i]->timeSpawn += loopTime;
		if (this->_itemList[i]->lifeTime <  this->_itemList[i]->timeSpawn)
			{this->_itemList.erase(_itemList.begin() + i);
	
		}
	}
}


void Referee::dropCoins(Enemy *src)
{
	this->_itemList.push_back(new Coin(src->x, src->y, this->loopTime , 10 ,Item::COINS, _res.texture["coin"]));
}
void Referee::playerInvinsibility(Player *player)
	{
		if (player->l_state == HIT)
		player->invTime += player->loopTime;
		if(player->invTime >= 1)
		{
			player->l_state = IN_LIFE;
			player->invTime = 0;
		}
	}
bool Referee::dealDamage(std::vector<Player *> &_player)
{
		int i;
		i = 0;
		while (i < _player.size())
		{
			playerInvinsibility(_player[i]);
			if (collideEnemy(_player[i], Event::I_NONE) == 2)
			_player[i]->getHit(1);
		i++;
		}
		i = 0;
		int c = 0;
		while (i < _player.size())
		{
			if (_player[i]->life <= 0 || _player[i]->y > Settings::HEIGHT + _player[i]->height )
				c++;
		i++;
		}
		if (c == _player.size())
			return false;
		return true;
}

void Referee::moveBullet(std::vector<Player *> &_player)
{
	for (int i = 0; i < this->_bulletList.size(); i++)
		{
			this->_bulletList[i]->x += this->_bulletList[i]->dirX *  this->_bulletList[i]->speed * (this->loopTime);
			this->_bulletList[i]->y += this->_bulletList[i]->dirY * this->_bulletList[i]->speed * ( this->loopTime);
			if( this->_bulletList[i]->destroy() == true)
				this->_bulletList.erase(this->_bulletList.begin() + i);
			else {
				for (int i2 = 0; i2 < this->_map.platform.size(); i2++)
				{
					if(this->_bulletList[i]->x  <= this->_map.platform[i2]->x  +  (this->_map.platform[i2]->length * Settings::CASE_SIZE)   && this->_bulletList[i]->x > this->_map.platform[i2]->x
						&&  this->_bulletList[i]->y >= this->_map.platform[i2]->y && this->_bulletList[i]->y <= this->_map.platform[i2]->y + Settings::CASE_SIZE
						
						)
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
			bool intersection;

			if (this->_enemyList[i2]->x  + Settings::CASE_SIZE < this->_bulletList[i]->x || this->_bulletList[i]->x < this->_enemyList[i2]->x
			||  this->_enemyList[i2]->y  + Settings::CASE_SIZE < this->_bulletList[i]->y || this->_bulletList[i]->y < this->_enemyList[i2]->y)
				{
					intersection = false;
				}
			else
			{
				intersection = true;
				this->_enemyList[i2]->getHit(this->_bulletList[i]->damage);
				this->_bulletList.erase(this->_bulletList.begin() + i);
				return ;
			}
		}
	}
	return;		   
}	