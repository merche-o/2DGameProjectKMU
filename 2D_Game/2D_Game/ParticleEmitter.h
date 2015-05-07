#pragma once

#include <vector>
#include "Particle.h"
#include "Pos.h"

class ParticleEmitter
{
public:
	float x;
	float y;
	std::vector<Particle*> emitter;
	sf::Color baseColor;
	bool changeColor;
	float timeCreate;
	float currentTime;
	int lifeTime;
	int radius;
	std::vector<Pos*> direction;
	float & loopTime;
	std::vector<sf::Color> randomColor;
	int numColor;
	int emissionTime;

public:
	ParticleEmitter(float X, float Y, float TimeCreate, int LifeTime, int Radius, sf::Color Color, float & LoopTime, bool ChangeColor, int EmissionTime = -1);
	~ParticleEmitter(void);

	void createParticle(float x, float y); // Ajoute une direction dans le vector de Pos
	void update();
};

