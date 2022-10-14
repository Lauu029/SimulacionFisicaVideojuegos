#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles();
protected:

	std::default_random_engine gen;
	std::uniform_real_distribution<> distribution{}
};

