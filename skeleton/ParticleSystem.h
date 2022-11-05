#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "ColorHSV.h"
#include "ParticleType.h"

enum typeParticleGenerator { font, fog, firework };
enum typeParticleSystem { particleGenerators, ForceGenerators };

class ParticleSystem
{
protected:
	vector <Particle*> particles;
	UniformParticleGenerator* fuente=nullptr;
	GaussianParticleGenerator* niebla=nullptr;
	UniformParticleGenerator* GravityParticles=nullptr;
	FireworkGenerator* fireworks=nullptr;
	vector<Firework*> f;
	typeParticleSystem _typeSystem;
public:
	ParticleSystem(typeParticleSystem pt);
	void ParticlesGravitySystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(typeParticleGenerator t);
	void generateFireworkSystem(FireworkType t);
	~ParticleSystem();
};