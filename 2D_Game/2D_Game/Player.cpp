//Marc

#include "Player.h"
#include "Settings.h"

Player::Player(Ressources & Ress, float &LoopTime, int NumPlayer)
	: AUnit(LoopTime), spell(x, y, LASER), numPlayer(NumPlayer)
{
	animFrame = 0;
	animDir = 1;
	isAlive = true;
	texture.loadFromFile("./Ressources/Images/Player.png");
	x = 500;
	y = 500;
	width = 32;
	height = 32;
	speed = 7 * Settings::CASE_SIZE;
	life = 5;
	shield = 0;
	
	score = 0;
	tmpTime = 0;
	inDash = 0;
	isPlayer = true;

	spellUsed = false;
	isSpell = true;
	cdTime = 10;

	particleColor = sf::Color(255, 255, 255);

	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer, Item::D_WEAPON));
	weapon[0]->spawnTime = 5;
	weaponUsed = 0;
	numWeapon = 0;
	invTime = 0;
}

void Player::init(Ressources &Ress)
{
	isAlive = true;
	animFrame = 0;
	animDir = 1;
	invTime = 0;
	x = 500;
	y = 500;
	life = 5;
	shield = 0;
	spellUsed = false;
	cdTime = 10;

	int i = 0;
	while (i < 11)
	{
		inputMap[i] = false;
		++i;
	}
	score = 0;
	weapon.clear();
	particles.clear();
	isPlayer = true;
	weapon.push_back(new Weapon(Ress.weapon[0]->damage, Ress.weapon[0]->fireRate, Ress.weapon[0]->range, Ress.weapon[0]->speed, numPlayer, Item::D_WEAPON));
	weaponUsed = 0;
	numWeapon = 0;
}


Player::~Player(void)
{
}


void Player::getNewWeapon(int weaponID, Ressources &Ress)
{
	if (Ress.weapon[weaponID])
		weapon.push_back(new Weapon(Ress.weapon[weaponID]->damage, Ress.weapon[weaponID]->fireRate, Ress.weapon[weaponID]->range, Ress.weapon[weaponID]->speed, numPlayer, Item::D_WEAPON));
}

void Player::explode()
{
	// Create Particles in explosionList

	sf::Color col(255, 255, 0);
	// ouest
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, -2, 0, 2, loopTime));
	// nord-ouest
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, -1, -1, 2, loopTime));
	// nord
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 0, -2, 2, loopTime));
	// nord-est
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 1, -1, 2, loopTime));
	// est
	explosionList.push_back(new Particle(x + width / 2, y + height / 2, col, 2, 2, 0, 2, loopTime));
}