#include "Particle.h"
#include "Settings.h"


Particle::Particle(float X, float Y, sf::Color Color, float & Time)
	: x(X), y(Y), color(Color), loopTime(Time)
{
	transp = 255;
	lifeTime = 1;
	speed = 3 * Settings::CASE_SIZE;
	texture.loadFromFile("./Ressources/Images/particle.png");
}


Particle::~Particle(void)
{
}

void Particle::update()
{
	currentTime += loopTime;
	transp = (lifeTime - currentTime) * 255 / lifeTime;
	if (transp < 0)
		transp = 0;
	//y -= speed * loopTime;
}