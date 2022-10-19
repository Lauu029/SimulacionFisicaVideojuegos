#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
protected:
	bool active;
	std::default_random_engine gen;
	std::uniform_real_distribution<> distribution{ -1,1 };

public:
	UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles();
	void setActive() { active = !active; };
	bool isActive() { return active; };
};

