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

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;

	state = U_NORMAL;
	jumpTmpY = 0;
	
	texture.loadFromFile(TextureFile);
	width = texture.getSize().x / 3;
	height = texture.getSize().y / 2;
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