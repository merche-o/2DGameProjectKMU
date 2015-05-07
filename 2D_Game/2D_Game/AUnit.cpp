// Olivier & Marc & Jors

#include "AUnit.h"
#include "Event.h"


AUnit::AUnit(float &LoopTime) : loopTime(LoopTime)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;
	fireRate = 5; // depend of the weapon
	fireRateCount = fireRate;
	timeDone = 0;
	for (int i = 0; i < 13; ++i)
	{
		inputMap.push_back(false);
	}
	doubleJump = true;
	fallingSpeed = 12 * Settings::CASE_SIZE;
	prevX = x;
	prevY = y;
	isPlayer = false;
}

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, std::string TextureFile, float &LoopTime)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime), loopTime(LoopTime)
{
	animFrame = 1;
	dir = LEFT;
	act = WALK;
	fireRate = 5; // depend of the weapon
	fireRateCount = fireRate;
	state = U_NORMAL;
	jumpTmpY = 0;
	l_state = IN_LIFE;
	texture.loadFromFile(TextureFile);
	width = texture.getSize().x;
	height = texture.getSize().y;
	fallingSpeed = 12 * Settings::CASE_SIZE;
	timeDone = 0;
	for (int i = 0; i < 13; ++i)
	{
		inputMap.push_back(false);
	}
	speed *= Settings::CASE_SIZE;
	doubleJump = true;
	prevX = x;
	prevY = y;
	isPlayer = false;
}

AUnit::AUnit(int Life, int Speed, int Damage, int SpawnTime, sf::Texture Texture, int X, int Y, e_dir Dir, float &LoopTime)
	: life(Life), speed(Speed), damage(Damage), spawnTime(SpawnTime), texture(Texture), x(X), y(Y), dir(Dir), loopTime(LoopTime)
{
	animFrame = 1;
	act = WALK;
	fireRate = 5; // depend of the weapon
	fireRateCount = fireRate;
	width = texture.getSize().x;
	height = texture.getSize().y;
	state = U_NORMAL;
	jumpTmpY = 0;
	l_state = IN_LIFE;
	timeDone = 0;
	
	for (int i = 0; i < 13; ++i)
	{
		inputMap.push_back(false);
	}
	doubleJump = true;
	fallingSpeed = 12 * Settings::CASE_SIZE;
	prevX = x;
	prevY = y;
	isPlayer = false;
}


AUnit::~AUnit(void)
{
}

void AUnit::nextFrame()
{
	animFrame++;
	if (animFrame >= 3)
		animFrame = 0;
}


void AUnit::getHit(int dam)
{
	if (this->shield > 0 && this->l_state != HIT)
	{
		this->l_state = HIT;
		this->shield -= dam;
		if (this->shield < 0)
			this->shield = 0;
	}	
	else if (this->life > 0 && this->l_state != HIT)
	{
		this->l_state = HIT;
		this->life -= dam;
	}

	if (this->life <= 0)
	{
		this->life = 0;
		this->l_state = DEAD;
	}
}

void AUnit::updateClock()
{
	this->weapon[weaponUsed]->fireRateCount -= loopTime;
}

void AUnit::createParticles()
{
	//generateParticle += loopTime;
	//if (generateParticle >= 0.03)
	{
		srand(loopTime * time(NULL));
		float xx = rand() % width + 0;
		float yy = rand() % height + 0;
		float s = rand() % 1 + 1;
		particles.push_back(new Particle(x + xx, y + yy, particleColor, 1, 0, 0, s, loopTime));
		generateParticle = 0;
	}
}

// Weapon : Very fast bullet, dropping lots of small particles on his trail, after one sec the particles grow really fast like exploding
// Particles popping randomly and going to a focused point (ex : Player charging exploding spell)
// Platforms appearing (Particles show the appearing platform)
// Enemies hit effect with particles (kind of chock/blooding effect