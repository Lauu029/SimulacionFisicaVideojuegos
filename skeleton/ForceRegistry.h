#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> forceParticlePair;

class ForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(float duration);
	void addRegistry(Particle*p, ForceGenerator* f);
	void deleteParticle(Particle*p);
	void deleteForce(ForceGenerator*f);
};




