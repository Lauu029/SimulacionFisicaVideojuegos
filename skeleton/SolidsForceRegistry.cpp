#include "SolidsForceRegistry.h"
#include <iostream>

void SolidsForceRegistry::updateForces(float duration)
{
	for (auto it = begin(); it != end(); it++)
		it->first->updateForce(it->second, duration);
}

void SolidsForceRegistry::addRegistry(Solids* rig, SolidsForceGenerator* f)
{
	insert({ f, rig });
}

void SolidsForceRegistry::deleteSolid(Solids* rig)
{
	for (auto it = begin(); it != end();)
	{
		if (it->second == rig)
			it = erase(it);
		else
			it++;
	}
}

void SolidsForceRegistry::deleteForce(SolidsForceGenerator* f)
{
	for (auto it = begin(); it != end();)
	{
		if (it->first == f)
			it = erase(it);
		else it++;
	}
}
