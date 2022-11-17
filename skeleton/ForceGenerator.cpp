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
	if (actionRate != nullptr) delete actionRate;
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

TorbellinoGenerator::TorbellinoGenerator(float r, Vector3 v, Vector3 p) :WindGenerator(r, v, p)
{
}

void TorbellinoGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	//𝐹𝑣	⃗⃗⃗ = 𝑘1(𝑣 𝑣 − 𝑣) + 𝑘2 ‖𝑣 𝑣 − 𝑣 ‖ (𝑣 𝑣 − 𝑣)
	float k = 5;

	vel = k * Vector3(-(p->getPos().z - pos.z), 50 - (p->getPos().y - pos.y),
		(p->getPos().x - pos.x));

	Vector3 v = p->getVel() - vel;
	float mod = v.normalize();
	mod = 1 * mod + 0 * powf(mod, 2);
	if (checkDistance(p))
		p->addForce(-v * mod);
}

ExplosionGenerator::ExplosionGenerator(float r, Vector3 p)
{
	actionRate = new Particle(forceActionRateParticle(r, p), true);
	radius = r;
	meanPose = p;
}

ExplosionGenerator::~ExplosionGenerator()
{
	if (actionRate != nullptr)
		delete actionRate;
}

void ExplosionGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;
	float k = 3;
	float R = 300000 * t;
	Vector3 particlePos = p->getPos();
	float r = sqrt(powf(particlePos.x - meanPose.x, 2) + powf(particlePos.y - meanPose.y, 2) + powf(particlePos.x - meanPose.x, 2));
	
	float explosionMultiply = exp(-(t / R));
	float x = k / radius * (p->getPos().x - meanPose.x) * explosionMultiply;
	float y = k / radius * (p->getPos().y - meanPose.y) * explosionMultiply;
	float z = k / radius * (p->getPos().z - meanPose.z) * explosionMultiply;

	if (r < R)
		p->addForce({ x, y, z });

}
