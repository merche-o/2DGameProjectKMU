#include "Player.h"


Player::Player(Ressources & Ress)
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = 0;
	y = 0;
	width = 32;
	height = 32;
	speed = 5;
	life = 5;
	shield = 3;
	score = 0;
	//weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed));
}


Player::~Player(void)
{
}
