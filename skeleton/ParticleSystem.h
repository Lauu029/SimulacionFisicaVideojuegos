#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "ColorHSV.h"
#include "ParticleType.h"

enum typeParticleSystem { font, fog, firework };

class ParticleSystem
{
protected:
	vector <Particle*> particles;
	UniformParticleGenerator* fuente;
	GaussianParticleGenerator* niebla;
	FireworkGenerator* fireworks;
	vector<Firework*> f;
public:
	ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(typeParticleSystem t);
	void generateFireworkSystem(FireworkType t);
	~ParticleSystem();
};