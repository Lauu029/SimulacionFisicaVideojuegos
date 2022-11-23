#pragma once

#include <list>
#include <iterator>

#include "ParticleGenerator.h"
#include "ParticleType.h"
#include "ForceRegistry.h"
#include "ForceGenerator.h"

enum typeParticleGenerator { font, fog, firework };
enum typeParticleSystem { particleGenerators, ForceGenerators, SpringsGenerators};
enum typeForceSystem { type_explosion, type_gravity, type_wind, type_torbellino };
class ParticleSystem
{
protected:
	vector <Particle*> particles;
	UniformParticleGenerator* fuente = nullptr;
	GaussianParticleGenerator* niebla = nullptr;
	UniformParticleGenerator* GravityParticles = nullptr;
	UniformParticleGenerator* WindParticles = nullptr;
	UniformParticleGenerator* TorbellinoParticles = nullptr;
	UniformParticleGenerator* ExplosionParticles = nullptr;
	FireworkGenerator* fireworks = nullptr;
	vector<Firework*> f;
	typeParticleSystem _typeSystem;
	ForceRegistry* fg = nullptr;
	GravityGenerator* gravity = nullptr;
	WindGenerator* wind = nullptr;
	TorbellinoGenerator* torbellino = nullptr;
	ExplosionGenerator* explosion = nullptr;

	vector<ForceGenerator*> springGenerators;
public:
	ParticleSystem(typeParticleSystem pt);
	void GenerateForceParticles(typeForceSystem tf);
	void update(double t);

	void addGravity();
	void deleteGravity();
	void addWind();
	void deleteWind();
	void addTorbellino();
	void deleteTorbellino();
	void addExplosion();

	void generateSpringDemo();
	ParticleGenerator* getParticleGenerator(typeParticleGenerator t);
	void generateFireworkSystem(FireworkType t);
	~ParticleSystem();
};