#include <list>

#include "ParticleGenerator.h"
#include "Particle.h"
class ParticleSystem
{
protected:
	list <Particle*> particles;
	list <ParticleGenerator*> particleGenerators;
public:
	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();

};

