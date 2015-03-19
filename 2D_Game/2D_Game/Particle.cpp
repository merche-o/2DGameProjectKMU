#include "Particle.h"
#include "Settings.h"


Particle::Particle(float X, float Y, float & Time)
	: x(X), y(Y), loopTime(Time)
{
	transp = 255;
	lifeTime = 2;
	speed = 3 * Settings::CASE_SIZE;
	texture.loadFromFile("./Ressources/Images/particle.png");

	color = sf::Color(255, 0, 0);
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
	y -= speed * loopTime;
}