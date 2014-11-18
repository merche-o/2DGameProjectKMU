#include "Item.h"


Item::Item(float X, float Y,  float LifeTime, sf::Texture Texture, itemType Type, int Score): x(X), y(Y), lifeTime(LifeTime), texture(Texture), type(Type), score(Score)
{
}

Item::Item(Item const & src) :x(src.x), y(src.y), spawnTime(src.spawnTime), lifeTime(src.lifeTime), texture(src.texture), type(src.type), score(src.score)
{
}

Item::Item()
	{
}





Item::~Item(void)
{
}