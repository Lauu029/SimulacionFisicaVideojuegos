#include "ParticleSystem.h"

void ParticleSystem::update(double t)
{
	for (auto p: particles)
	{
		if (p->getPos().y < 0) {
			delete p;
		}
		else
			p->integrate(t);
	}
	for (auto pg: particleGenerators)
	{
		list<Particle*> newParticles = pg->generateParticles();
		for (auto a: newParticles)
			particles.push_back(a);
		newParticles.clear();20.
	}
}

ParticleSystem::~ParticleSystem()
{
	for (auto p: particles)
	{
		delete p;
	}
	particles.clear();
	for (auto pg: particleGenerators)
	{
		delete pg;
	}
	particleGenerators.clear();
}
