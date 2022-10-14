#include "ParticleGenerator.h"
class UniformParticleGenerator : public ParticleGenerator
{
private:
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles();
public:
};

