#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter(float X, float Y, float TimeCreate, int LifeTime, int Radius, sf::Color Color, float & LoopTime, bool ChangeColor, int EmissionTime)
	: x(X), y(Y), timeCreate(TimeCreate), lifeTime(LifeTime), radius(Radius), baseColor(Color), loopTime(LoopTime), changeColor(ChangeColor), emissionTime(EmissionTime)
{
	currentTime = 0;

	numColor = 0;
	randomColor.push_back(sf::Color(250,50,50));
	randomColor.push_back(sf::Color(150,150,50));
	randomColor.push_back(sf::Color(50,250,50));
	randomColor.push_back(sf::Color(50,150,150));
	randomColor.push_back(sf::Color(50,50,250));
	randomColor.push_back(sf::Color(150,50,150));
}


ParticleEmitter::~ParticleEmitter(void)
{
}

void ParticleEmitter::createParticle(float x, float y)
{
	direction.push_back(new Pos(x, y));
}

void ParticleEmitter::update()
{
	currentTime += loopTime;

	if (currentTime >= timeCreate && emissionTime != 0)
	{
		for (int i = 0; i < direction.size(); ++i)
		{
			if (changeColor == true)
			{
				numColor++;
				if (numColor >= randomColor.size())
					numColor = 0;
				emitter.push_back(new Particle(x, y, randomColor[numColor], lifeTime, direction[i]->x, direction[i]->y, radius, loopTime));
			}
			else
				emitter.push_back(new Particle(x, y, baseColor, lifeTime, direction[i]->x, direction[i]->y, radius, loopTime));
		}
		currentTime = 0;
		emissionTime--;
	}
	
	for (int i = 0; i < emitter.size(); ++i)
	{
		emitter[i]->update();
	}
}