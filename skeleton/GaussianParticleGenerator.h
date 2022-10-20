#pragma once

#include "ParticleGenerator.h"
class GaussianParticleGenerator: public ParticleGenerator
{
protected:
	std::default_random_engine ran;
	std::normal_distribution<> dist{ 0.5, 0.5 };
};

