#include "AUnit.h"


AUnit::AUnit(void)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;
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