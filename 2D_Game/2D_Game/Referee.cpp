#include "Referee.h"


Referee::Referee(std::vector<AUnit*> & enemylist, std::vector<Item*> const &itemList, Map &map) 
: _enemyList(enemylist), _itemList(itemList), _map(map)
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
			if (src->x > this->_map.platform[i]->x && src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE && src->y >= this->_map.platform[i]->y)
				{				
				while (src->x > this->_map.platform[i]->x && src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y < this->_map.platform[i]->y + Settings::CASE_SIZE && src->y > this->_map.platform[i]->y)
					src->y += 1;
				return 1;
				}
			else if (src->x+ Settings::CASE_SIZE  > this->_map.platform[i]->x && src->x+ Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE && src->y >= this->_map.platform[i]->y)
				{				
				while (src->x+ Settings::CASE_SIZE > this->_map.platform[i]->x && src->x+ Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y < this->_map.platform[i]->y + Settings::CASE_SIZE && src->y > this->_map.platform[i]->y)
					src->y += 1;
				return 1;
				}
			}
		}
	if (btn == Event::I_RIGHT)
	{
		for (int i = 0; i < this->_map.platform.size(); i++)
		{
			if (src->x + Settings::CASE_SIZE >= this->_map.platform[i]->x  && src->x + Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x + Settings::CASE_SIZE > this->_map.platform[i]->x && src->x + Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&& src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
					src->x -= 1;
				return 1;
			}
			else if (src->x + Settings::CASE_SIZE >= this->_map.platform[i]->x && src->x + Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x + Settings::CASE_SIZE > this->_map.platform[i]->x && src->x + Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&& src->y+ Settings::CASE_SIZE >= this->_map.platform[i]->y && src->y+ Settings::CASE_SIZE <= this->_map.platform[i]->y + Settings::CASE_SIZE)
					src->x -= 1;
				return 1;
			}
		}
	}
	if (btn == Event::I_LEFT)
	{
		for (int i = 0; i < this->_map.platform.size(); i++)
		{
			if (src->x  <= this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length && src->x > this->_map.platform[i]->x
			&&  src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length  && src->x > this->_map.platform[i]->x
			&& src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
					src->x += 1;
				src->x += 10;
				src->x += src->speed;
				return 1;
			}
			else if (src->x  <= this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length && src->x > this->_map.platform[i]->x
			&&  src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length  && src->x > this->_map.platform[i]->x
			&& src->y >= this->_map.platform[i]->y && src->y <= this->_map.platform[i]->y + Settings::CASE_SIZE)
					src->x += 1;
				src->x += 10;
				src->x += src->speed;
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
	
	return -1;
}

bool  Referee::applyGravity(AUnit  *src)
{
	
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;

	for (int i = 0; i < this->_map.platform.size(); i++)
	{
		if (src->x > this->_map.platform[i]->x  && src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y + Settings::CASE_SIZE >= this->_map.platform[i]->y && src->y + Settings::CASE_SIZE < this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x > this->_map.platform[i]->x && src->x < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&& src->y + Settings::CASE_SIZE > this->_map.platform[i]->y && src->y + Settings::CASE_SIZE < (this->_map.platform[i]->y + Settings::CASE_SIZE))
					src->y -= 1;
				return false;
			}
		else if (src->x+ Settings::CASE_SIZE  > this->_map.platform[i]->x  && src->x+ Settings::CASE_SIZE < this->_map.platform[i]->x +  Settings::CASE_SIZE * this->_map.platform[i]->length
			&&  src->y + Settings::CASE_SIZE >= this->_map.platform[i]->y && src->y + Settings::CASE_SIZE < this->_map.platform[i]->y + Settings::CASE_SIZE)
			{				
				while (src->x+ Settings::CASE_SIZE > this->_map.platform[i]->x  && src->x+ Settings::CASE_SIZE < this->_map.platform[i]->x + Settings::CASE_SIZE * this->_map.platform[i]->length
			&& src->y + Settings::CASE_SIZE > this->_map.platform[i]->y && src->y + Settings::CASE_SIZE < (this->_map.platform[i]->y + Settings::CASE_SIZE))
					src->y -= 1;
				return false;
			}
	}
	return true;
}

void Referee::cleanEnemyList()
{
	for (int i = 0; i < this->_enemyList.size(); i++)
	{
		if (this->_enemyList[i]->y > Settings::HEIGHT)
			this->_enemyList.erase(_enemyList.begin() + i);
	}
}