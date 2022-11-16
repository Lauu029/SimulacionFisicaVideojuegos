#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "ParticleType.h"
#include "ForceRegistry.h"
#include "ForceGenerator.h"

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
	ForceRegistry* fg = nullptr;
	ForceGenerator* gravity = nullptr;
	ForceGenerator* wind = nullptr;
public:
	ParticleSystem(typeParticleSystem pt);
	void ParticlesGravitySystem();
	void update(double t);
	void addGravity();
	void deleteGravity();
	void addWind();
	void deleteWind();
	ParticleGenerator* getParticleGenerator(typeParticleGenerator t);
	void generateFireworkSystem(FireworkType t);
	~ParticleSystem();
};