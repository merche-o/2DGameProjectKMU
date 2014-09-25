#include "Player.h"


Player::Player(void)
	: AUnit()
{
	texture.loadFromFile("Character.png");
	x = 150;
	y = 150;
}


Player::~Player(void)
{
}
