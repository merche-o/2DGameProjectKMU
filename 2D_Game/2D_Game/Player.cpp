#include "Player.h"


Player::Player(void)
	: AUnit()
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = 150;
	y = 150;
	width = 32;
	height = 32;
}


Player::~Player(void)
{
}
