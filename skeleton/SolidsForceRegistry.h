#pragma once
#include <map>
#include "SolidsForceGenerator.h"

typedef std::pair<SolidsForceGenerator*, Solids*> forceSolidPair;

class SolidsForceRegistry : public std::multimap<SolidsForceGenerator*, Solids*> {
public:
	void updateForces(float duration);
	void addRegistry(Solids*rig, SolidsForceGenerator* f);
	void deleteSolid(Solids*rig);
	void deleteForce(SolidsForceGenerator* f);
};
