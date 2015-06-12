#include "Particle.h"
#include "Settings.h"


Particle::Particle(float X, float Y, sf::Color Color, float LifeTime, float SpeedX, float SpeedY, float Radius, float & Time)
	: x(X), y(Y), color(Color), lifeTime(LifeTime), radius(Radius), loopTime(Time), speed(SpeedX * Settings::CASE_SIZE, SpeedY * Settings::CASE_SIZE)
{
	transp = 255;

	float tmp;
	tmp = lifeTime / 6;

	lifeGradient.push_back(lifeTime);
	lifeGradient.push_back(tmp * 5);
	lifeGradient.push_back(tmp * 4);
	lifeGradient.push_back(tmp * 3);
	lifeGradient.push_back(tmp * 2);
	lifeGradient.push_back(tmp);
	
	transpGradient.push_back(0);
	transpGradient.push_back(50);
	transpGradient.push_back(100);
	transpGradient.push_back(150);
	transpGradient.push_back(200);
	transpGradient.push_back(250);
	currentTime = 0;
}


Particle::~Particle(void)
{
}

void Particle::update()
{
	currentTime += loopTime;

	for (int i = 0; i < lifeGradient.size(); ++i)
	{
		if (currentTime >= lifeGradient[i])
		{
			transp = transpGradient[i];
			break;
		}
	}

	y += speed.y * loopTime;
	x += speed.x * loopTime;
}