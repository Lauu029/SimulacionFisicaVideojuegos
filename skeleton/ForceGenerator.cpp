#include "ForceGenerator.h"

GravityGenerator::GravityGenerator(const Vector3& g)
{
	gravity = g;
}

void GravityGenerator::updateForce(Particle* p, float t)
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
	if (actionRate != nullptr) {
		delete actionRate;
		actionRate = nullptr;
	}
}

void WindGenerator::updateForce(Particle* p, float t)
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

TorbellinoGenerator::~TorbellinoGenerator()
{
}

void TorbellinoGenerator::updateForce(Particle* p, float t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	//𝐹𝑣	⃗⃗⃗ = 𝑘1(𝑣 𝑣 − 𝑣) + 𝑘2 ‖𝑣 𝑣 − 𝑣 ‖ (𝑣 𝑣 − 𝑣)
	float k = 5;

	vel = k * Vector3(-(p->getPos().z - pos.z), 50 - (p->getPos().y - pos.y),
		(p->getPos().x - pos.x));

	Vector3 v = p->getVel() - vel;
	float mod = v.normalize();
	mod = 3 * mod + 0 * powf(mod, 2);
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
	if (actionRate != nullptr) {
		delete actionRate;
		actionRate = nullptr;
	}
}

void ExplosionGenerator::updateForce(Particle* p, float t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;
	float k = 2000;
	float R = 3000000 * t;
	Vector3 particlePos = p->getPos();
	float r = sqrt(powf(particlePos.x - meanPose.x, 2) + powf(particlePos.y - meanPose.y, 2) + powf(particlePos.x - meanPose.x, 2));

	float explosionMultiply = exp(-(t / 2));
	float x = k / radius * (p->getPos().x - meanPose.x) * explosionMultiply;
	float y = k / radius * (p->getPos().y - meanPose.y) * explosionMultiply;
	float z = k / radius * (p->getPos().z - meanPose.z) * explosionMultiply;

	if (r < R)
		p->addForce({ x, y, z });

}

SpringForceGenerator::SpringForceGenerator(float _k, float resting_Length, Particle* other)
{
	k = _k;
	restingLength = resting_Length;
	particle = other;
}

void SpringForceGenerator::updateForce(Particle* p, float t)
{
	if (p->getMass() <= 0)
		return;

	Vector3 f = particle->getPos() - p->getPos();

	const float l = f.normalize();
	const float delta_x = l - restingLength;

	f *= delta_x * k;

	p->addForce(f);
}

SpringForceGenerator::~SpringForceGenerator()
{
	particle = nullptr;
}

AnchoredSpringFG::AnchoredSpringFG(float _k, float _resting, const Vector3& anchor_pos) :SpringForceGenerator(_k, _resting, nullptr)
{
	particle = new Particle(RigidBox(anchor_pos), true);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	if (particle != nullptr)
		delete particle;
}

GomaElasticaGenerator::GomaElasticaGenerator(float _k, float resting_Length, Particle* other) :
	SpringForceGenerator(_k, resting_Length, other)
{
}

void GomaElasticaGenerator::updateForce(Particle* p, float t)
{
	if (p->getMass() <= 0) return;

	Vector3 f = particle->getPos() - p->getPos();

	if (f.magnitude() > restingLength) {
		const float l = f.normalize();
		const float delta_x = l - restingLength;

		f *= delta_x * k;

		p->addForce(f);
	}
}

ParticleDragGenerator::ParticleDragGenerator(const float _k1, const float _k2) :k1(_k1), k2(_k2)
{
}

void ParticleDragGenerator::updateForce(Particle* p, float t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	Vector3 v = p->getVel();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = k1 * drag_coef + k2 * powf(drag_coef, 2);
	dragF = -v * drag_coef;

	p->addForce(dragF);
}

BuoyancyForceGenerator::BuoyancyForceGenerator(float mD, float h, float V, float d, Vector3 pos) :maxDepth(mD), height(h), volume(V), liquidDensity(d)
{
	liquid = new Particle(Liquid(pos), true);
}

void BuoyancyForceGenerator::updateForce(Particle* p, float t)
{
	float depth;

	depth = p->getPos().y;
	Vector3 f(0.0f, 0.0f, 0.0f);

	//Above plane
	if (depth > (height + maxDepth))
		return;

	if (depth < (height - maxDepth)) {
		f.y = liquidDensity * volume * gravity;
	}
	else {
		float depthExt = height + maxDepth;
		float volFactor = (depthExt - depth) / (2 * maxDepth);
		f.y = liquidDensity * volume * volFactor * gravity;
	}
	p->addForce(f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	if (liquid != nullptr)
		delete liquid;
}
