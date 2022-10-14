#include <list>

#include "ParticleGenerator.h"


class ParticleSystem
{
protected:
	list <Particle*> particles;
public:
	list <ParticleGenerator*> particleGenerators;
	ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
	~ParticleSystem();
};

