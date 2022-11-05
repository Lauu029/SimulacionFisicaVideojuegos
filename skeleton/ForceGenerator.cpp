#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(const Vector3& g)
{
	gravity = g;
}

void GravityGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;
	p->addForce(gravity * p->getMass());
}
