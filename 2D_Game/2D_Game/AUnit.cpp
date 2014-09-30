#include "AUnit.h"
#include "Event.h"


AUnit::AUnit(void)
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
	state = U_NORMAL;
	texture.loadFromFile(TextureFile);
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