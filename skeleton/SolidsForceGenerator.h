#include "Solids.h"
#include <list>
#include <random>
#include "Particle.h"
using namespace physx;
class SolidsForceGenerator
{
public:
	virtual void updateForce(Solids* rig, float t) = 0;
	Particle* actionRate = nullptr;
};

class SolidsWindGenerator : public SolidsForceGenerator {
public:
	SolidsWindGenerator(float r, Vector3 v, Vector3 p);
	virtual ~SolidsWindGenerator();
	virtual void updateForce(Solids* rig, float t) override;
	void changeWindForce(Vector3 v) { vel = v; };
protected:
	bool checkDistance(Solids* rig);
	float radius = 0;
	Vector3 pos;
	Vector3 vel;
};
