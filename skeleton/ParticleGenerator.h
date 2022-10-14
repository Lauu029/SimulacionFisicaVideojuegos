
#include <string>
#include <list>

#include "Particle.h"
using namespace std;
class ParticleGenerator
{
protected:
	string name;
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* model;

	void setParticle(Particle* _m);
	virtual list <Particle*> generateParticles()=0;
public:
	ParticleGenerator();
	~ParticleGenerator();
	void update(double t);
};

