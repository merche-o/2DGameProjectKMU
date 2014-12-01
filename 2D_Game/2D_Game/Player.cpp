#include "Player.h"
#include "Settings.h"


Player::Player(Ressources & Ress, float &LoopTime, int NumPlayer): AUnit(LoopTime), numPlayer(NumPlayer)
{
	texture.loadFromFile("../Ressources/Images/Player.png");
	x = -2;
	y = 0;
	width = 32;
	height = 32;
	speed = 7 * Settings::CASE_SIZE;
	life = 3;
	shield = 3;
	
	score = 0;

	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer));

	//weapon[0]->

	//weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed));
}

void Player::init(Ressources &Ress)
	{
		x = -2;
	y = 0;
	life = 3;
	shield = 3;
	int i = 0;
	while (i < 9)
	{
		inputMap[i] = false;
		++i;
	}
	score = 0;
	weapon.clear();
	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer));
	isPlayer = true;
}


Player::~Player(void)
{
}

