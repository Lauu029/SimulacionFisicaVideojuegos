#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "ColorHSV.h"
#include "ParticleType.h"

enum typeParticleSystem { font, fog };
class ParticleSystem
{
protected:
	vector <Particle*> particles;
	UniformParticleGenerator* fuente;
	GaussianParticleGenerator* niebla;

public:
	ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(typeParticleSystem t);
	void generateFireworkSystem();
	~ParticleSystem();
};