#include "Referee.h"


Referee::Referee(std::vector<AUnit*> & enemylist, std::vector<Item*>  &itemList, std::vector<Bullet *> &bulletList ,Map &map, float &LoopTime) 
: _enemyList(enemylist), _itemList(itemList),_bulletList(bulletList), _map(map), loopTime(LoopTime)
{
	collideManager.push_back(&Referee::collideEnemy);
	collideManager.push_back(&Referee::collideBonus);
	collideManager.push_back(&Referee::collideWall);
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
	return -1;
}

int Referee::collideWall(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_UP)
		{
			for (int i = 0; i < this->_map.platform.size(); i++)
			{
			if (		src->x							>	this->_map.platform[i]->x &&
						src->x							<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
						src->y							<=	this->_map.platform[i]->y + Settings::CASE_SIZE &&
						src->y							>=	this->_map.platform[i]->y)
				{
					src->y = this->_map.platform[i]->y + Settings::CASE_SIZE + 1;
					return 1;
				}
			else if (	src->x + Settings::CASE_SIZE	>	this->_map.platform[i]->x &&
						src->x + Settings::CASE_SIZE	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
						src->y							<=	this->_map.platform[i]->y + Settings::CASE_SIZE &&
						src->y							>=	this->_map.platform[i]->y)
				{				
					src->y = this->_map.platform[i]->y + Settings::CASE_SIZE + 1;
					return 1;
				}
			}
		}
	if (btn == Event::I_RIGHT)
	{
		for (int i = 0; i < this->_map.platform.size(); i++)
		{
			if (		src->x + Settings::CASE_SIZE	>=	this->_map.platform[i]->x  &&
						src->x + Settings::CASE_SIZE	<	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
						src->y							>=	this->_map.platform[i]->y &&
						src->y							<=	this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				src->x = this->_map.platform[i]->x - Settings::CASE_SIZE;
				return 1;
			}
		}
	}
	if (btn == Event::I_LEFT)
	{
		for (int i = 0; i < this->_map.platform.size(); i++)
		{
			if (		src->x							<=	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
						src->x							>	this->_map.platform[i]->x &&
						src->y							>=	this->_map.platform[i]->y &&
						src->y							<=	this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				src->x = this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length;
				return 1;
			}
		}
	}

	//if (btn == Event::I_DOWN)
	//{
		//if (this->_map.map[std::make_pair((src->y + src->height)/Settings::CASE_SIZE, src->x/Settings::CASE_SIZE)].type == WALL)
	//	{	
			
		//	return 2;
		//}
	//}
		
	return -1;
}

int Referee::collideEnemy(AUnit  *src, Event::Input const &btn)
{
	if (btn == Event::I_NONE)
	{
		for (int i = 0; i < this->_enemyList.size(); i++)
		{
			if (src->x  <= this->_enemyList[i]->x + Settings::CASE_SIZE  && src->x > this->_enemyList[i]->x
			&&  src->y >= this->_enemyList[i]->y && src->y <= this->_enemyList[i]->y + Settings::CASE_SIZE)
		return 2;
		}
	}
	return -1;
}

bool  Referee::applyGravity(AUnit  *src)
{
	
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;

	for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_LEFT)
			src->x -= 1;
		else if (this->_map.platform[i]->isMorphing == true && this->_map.platform[i]->type == Platform::platform_type::GO_RIGHT)
			src->x += 1;

		if (		src->x							>=	this->_map.platform[i]->x  &&
					src->x							<=	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
					src->y + Settings::CASE_SIZE	>=	this->_map.platform[i]->y &&
					src->y + Settings::CASE_SIZE	<	this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				src->y = this->_map.platform[i]->y - Settings::CASE_SIZE;
				return false;
			}
		else if (	src->x + Settings::CASE_SIZE	>=	this->_map.platform[i]->x  &&
					src->x + Settings::CASE_SIZE	<=	this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length &&
					src->y + Settings::CASE_SIZE	>=	this->_map.platform[i]->y &&
					src->y + Settings::CASE_SIZE	<	this->_map.platform[i]->y + Settings::CASE_SIZE)
			{
				src->y = this->_map.platform[i]->y - Settings::CASE_SIZE;
				return false;
			}
	}
	return true;
}

void Referee::cleanEnemyList()
{
	for (int i = 0; i < this->_enemyList.size(); i++)
	{
		if (this->_enemyList[i]->y > Settings::HEIGHT  || this->_enemyList[i]->l_state == DEAD)
			this->_enemyList.erase(_enemyList.begin() + i);
	}
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

void Referee::moveBullet()
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
	this->bulletHit();

	return;
}

void Referee::bulletHit()
{				   
	for (int i = 0; i < this->_bulletList.size(); i++)
	{
		for (int i2 = 0; i2 < this->_enemyList.size(); i2++)
		{
			if (this->_bulletList[i]->x  <= this->_enemyList[i2]->x + Settings::CASE_SIZE  && this->_bulletList[i]->x > this->_enemyList[i2]->x
			&&  this->_bulletList[i]->y >= this->_enemyList[i2]->y && this->_bulletList[i]->y <= this->_enemyList[i2]->y + Settings::CASE_SIZE)
				{
					this->_enemyList[i2]->getHit(this->_bulletList[i]->damage);
					this->tmp = (Player *)this->_bulletList[i]->player;
					tmp->score += 10;
					this->_bulletList.erase(this->_bulletList.begin() + i);
				
				}
		}
	}
	return;		   
}	