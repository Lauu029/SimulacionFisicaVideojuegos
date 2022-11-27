#include "ForceRegistry.h"
#include <iostream>

void ForceRegistry::updateForces(float duration)
{
	for (auto it = begin(); it != end(); it++)
		it->first->updateForce(it->second,duration);
}

void ForceRegistry::addRegistry(Particle* p, ForceGenerator* f)
{
	insert({ f, p });
}

void ForceRegistry::deleteParticle(Particle* p)
{
	for (auto it = begin(); it != end();)
	{
		if (it->second == p)
			it = erase(it);
		else
			it++;
	}
}

void ForceRegistry::deleteForce(ForceGenerator* f)
{
	for (auto it = begin(); it != end();)
	{
		if (it->first == f)
			it = erase(it);
		else it++;
	}
}
