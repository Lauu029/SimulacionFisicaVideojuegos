#include "SolidsForceGenerator.h"

SolidsWindGenerator::SolidsWindGenerator(float r, Vector3 v, Vector3 p)
{
	actionRate = new Particle(forceActionRateParticle(r, p), true);
	radius = r;
	vel = v;
	pos = p;
}
SolidsWindGenerator::~SolidsWindGenerator()
{
	if (actionRate != nullptr) {
		delete actionRate;
		actionRate = nullptr;
	}	
}
 
void SolidsWindGenerator::updateForce(Solids* rig, float t)
{
	float k = 0.8;

	if (checkDistance(rig))
		rig->addForce(k * (vel - rig->getVel()));
}

bool SolidsWindGenerator::checkDistance(Solids* rig) {
	Vector3 solidPos = rig->getPos();
	return (solidPos.x <= pos.x + radius && solidPos.x >= pos.x - radius)
		&& (solidPos.y <= pos.y + radius && solidPos.y >= pos.y - radius)
		&& (solidPos.z <= pos.z + radius && solidPos.z >= pos.z - radius);
}