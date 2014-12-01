#include "Ammo.h"


Ammo::Ammo(float X, float Y, float LifeTime,float LoopTime, sf::Texture texture, Item::itemType Itype, Item::itemType weapon)
	:Item(X,Y,LifeTime,texture,Itype,0),  weaponType(weapon) 
{
	this->timeSpawn = 0;
}


Ammo::~Ammo(void)
{
}
