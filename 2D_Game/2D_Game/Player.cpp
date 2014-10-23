#include "Player.h"


Player::Player(Ressources & Ress, float &LoopTime): AUnit(LoopTime)
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = -2;
	y = 0;
	width = 32;
	height = 32;
	speed = 5;
	life = 5;
	shield = 3;
	invTime = 0;
	score = 0;

	//weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed));
}


Player::~Player(void)
{
}

