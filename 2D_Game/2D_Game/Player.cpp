#include "Player.h"
#include "Settings.h"


Player::Player(Ressources & Ress, float &LoopTime, int NumPlayer)
	: AUnit(LoopTime), spell(x, y), numPlayer(NumPlayer)
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
	tmpTime = 0;
	inDash = 0;
	spell.type = LASER;
	isPlayer = true;
	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer, Item::D_WEAPON));
	//weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed));
}

void Player::init(Ressources &Ress)
{
	x = -2;
	y = 0;
	life = 2;
	shield = 1;
	int i = 0;
	while (i < 9)
	{
		inputMap[i] = false;
		++i;
	}
	score = 0;
	weapon.clear();
	isPlayer = true;
	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer, Item::D_WEAPON));
}


Player::~Player(void)
{
}

