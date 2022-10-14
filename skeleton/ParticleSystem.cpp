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
