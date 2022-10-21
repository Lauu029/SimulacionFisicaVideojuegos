#pragma once

#include <string>
#include <list>
#include <random>

#include "Particle.h"
using namespace std;
class ParticleGenerator
{
protected:
	string name;
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* model;
	bool active;
	
public:
	void setParticle(Particle* _m) { model = _m; };
	virtual list <Particle*> generateParticles() = 0;
	void setActive() { active = !active; };
	bool isActive() { return active; };
	~ParticleGenerator();
};

class UniformParticleGenerator : public ParticleGenerator
{
protected:
	std::default_random_engine gen;
	std::uniform_real_distribution<> distribution{ -1,1 };

public:
	UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles() override;
};

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
	std::default_random_engine ran;
	std::normal_distribution<> dist{ 0.5, 0.5 };
public:
	GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles() override;
};

