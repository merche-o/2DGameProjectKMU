#include "Player.h"


Player::Player(void)
	: AUnit()
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = 608;
	y = 352;
	width = 32;
	height = 32;
}


Player::~Player(void)
{
}
