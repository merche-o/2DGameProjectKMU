#include "AUnit.h"


AUnit::AUnit(void)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;
}

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime)
{
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