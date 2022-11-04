#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, double t);
	std::string name;
	double t = -1e10;
};

