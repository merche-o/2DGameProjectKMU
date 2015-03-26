#include "Particle.h"
#include "Settings.h"


Particle::Particle(float X, float Y, sf::Color Color, float LifeTime, int Speed, e_type Type, float & Time)
	: x(X), y(Y), color(Color), lifeTime(LifeTime), type(Type), loopTime(Time)
{
	transp = 255;
	speed = Speed * Settings::CASE_SIZE;
	//texture.loadFromFile("./Ressources/Images/particle.png");
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
	
	if (type == UP)
		y -= speed * loopTime;
	else if (type == DOWN)
		y += speed * loopTime;
	else if (type == DISPERSE)
	{
		// Random direction (un vecteur directeur) and color
	}
}