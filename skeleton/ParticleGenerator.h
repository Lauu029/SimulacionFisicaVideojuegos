
#include <string>
#include <list>
#include <random>

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
public:
	void setParticle(Particle* _m) { model = _m; };
	virtual list <Particle*> generateParticles() = 0;
};

