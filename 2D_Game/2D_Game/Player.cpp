#include "Player.h"


Player::Player()
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = 608;
	y = 352;
	width = 32;
	height = 32;
	speed = 5;
}


Player::~Player(void)
{
}
