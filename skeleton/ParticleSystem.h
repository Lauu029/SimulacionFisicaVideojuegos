#pragma once

#include <list>

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"

class ParticleSystem
{
protected:
	list <Particle*> particles;
public:
	list <ParticleGenerator*> particleGenerators;
	ParticleSystem(){};
	void update(double t);
	void addParticleGenerator();
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
	~ParticleSystem();
};

