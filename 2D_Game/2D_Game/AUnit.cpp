#include "AUnit.h"
#include "Event.h"


AUnit::AUnit()
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;

	int i = 0;
	while (i < 9)
	{
		inputMap.push_back(false);
		++i;
	}
}

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile, float &LoopTime)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime), loopTime(LoopTime)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;

	state = U_NORMAL;
	jumpTmpY = 0;
	l_state = IN_LIFE;
	texture.loadFromFile(TextureFile);
	width = texture.getSize().x / 3;
	height = texture.getSize().y / 2;
	fallingSpeed = 5;
		int i = 0;
	while (i < 9)
	{
		inputMap.push_back(false);
		++i;
	}
}

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, float &LoopTime)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime), texture(Texture), x(X), y(Y), dir(Dir), loopTime(LoopTime)
{
	animFrame = 1;
	act = WALK;
	width = texture.getSize().x / 3;
	height = texture.getSize().y / 2;
	state = U_NORMAL;
	jumpTmpY = 0;
	l_state = IN_LIFE;
	
		int i = 0;
	while (i < 9)
	{
		inputMap.push_back(false);
		++i;
	}
}


AUnit::~AUnit(void)
{
}

void AUnit::nextFrame()
{
	animFrame++;
	if (animFrame >= 3)
		animFrame = 0;
}


void AUnit::getHit(int dam)
{
		this->l_state = HIT;
		if (this->shield > 0)
			{
				this->shield-= dam;
				if (this->shield < 0)
					this->shield = 0;
			}	
		else if (this->life > 0)
			this->life-=dam;
		if (this->life <= 0)
			{
				this->life = 0;
				this->l_state = DEAD;
			}

}