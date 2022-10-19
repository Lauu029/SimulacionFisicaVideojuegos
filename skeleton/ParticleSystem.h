#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
enum typeParticleSystem { font, fog };
class ParticleSystem
{
protected:
	vector <Particle*> particles;
	UniformParticleGenerator* fuente;
	UniformParticleGenerator* niebla;

public:
	vector <ParticleGenerator*> particleGenerators;

	ParticleSystem();
	void update(double t);
	void setParticleGenerators(typeParticleSystem type);
	void activateParticleGenerators(typeParticleSystem type);
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
	~ParticleSystem();
};

