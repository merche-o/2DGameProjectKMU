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


AUnit::~AUnit(void)
{
}

void AUnit::nextFrame()
{
	animFrame++;
	if (animFrame >= 3)
		animFrame = 0;
}