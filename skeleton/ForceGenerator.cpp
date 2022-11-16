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

WindGenerator::WindGenerator(float r, Vector3 v, Vector3 p)
{
	actionRate = new Particle(forceActionRateParticle(r, p), true);
	radius = r;
	vel = v;
	pos = p;
}

WindGenerator::~WindGenerator()
{
	if (actionRate != nullptr)
		delete actionRate;
}

void WindGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	//𝐹𝑣	⃗⃗⃗ = 𝑘1(𝑣 𝑣 − 𝑣) + 𝑘2 ‖𝑣 𝑣 − 𝑣 ‖ (𝑣 𝑣 − 𝑣)
	float k = 0.8;

	if (checkDistance(p))
		p->addForce(k * (vel - p->getVel()));
}

bool WindGenerator::checkDistance(Particle* p)
{
	Vector3 particlePos = p->getPos();
	return (particlePos.x <= pos.x + radius && particlePos.x >= pos.x - radius)
		&& (particlePos.y <= pos.y + radius && particlePos.y >= pos.y - radius)
		&& (particlePos.z <= pos.z + radius && particlePos.z >= pos.z - radius);
}

TorbellinoGenerator::TorbellinoGenerator()
{
}

TorbellinoGenerator::~TorbellinoGenerator()
{
}

void TorbellinoGenerator::updateForce(Particle* p, double t)
{
}

ExplosionGenerator::ExplosionGenerator()
{
}

ExplosionGenerator::~ExplosionGenerator()
{
}

void ExplosionGenerator::updateForce(Particle* p, double t)
{
}
