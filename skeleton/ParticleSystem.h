#include <list>

#include "ParticleGenerator.h"


class ParticleSystem
{
protected:
	list <Particle*> particles;
	list <ParticleGenerator*> particleGenerators;
public:
	ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
	~ParticleSystem();
};

