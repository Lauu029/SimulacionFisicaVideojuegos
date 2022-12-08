#pragma once

#include <string>
#include <list>
#include <random>
#include <complex>
#include "Particle.h"
#include "Solids.h"

using namespace std;
using namespace physx;

class ParticleGenerator
{
protected:
	Vector3 meanPos, meanVel;
	int numParticles;
	Particle* model;
	bool active;

public:
	void setParticle(Particle* _m) { model = _m; };
	virtual list <Particle*> generateParticles() = 0;
	void setActive() { active = !active; };
	bool isActive() { return active; };
	~ParticleGenerator();
	std::random_device rd;
	std::default_random_engine gen;
	std::uniform_real_distribution<> distribution{ -1,1 };
	std::normal_distribution<> dist{ 0.5, 0.5 };
};

class UniformParticleGenerator : public ParticleGenerator
{
protected:
	bool move;
	int sep;
public:
	UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel, int n, bool m, int s);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles() override;
	void newParticleType();
};

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
public:
	GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	list<Particle*> generateParticles() override;
};
class GaussianSolidsGenerator : public GaussianParticleGenerator
{
protected:
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;
	RenderItem* gItem = nullptr;
	PxShape* gShape = nullptr;
	list<Solids*> solids;
public:
	GaussianSolidsGenerator(PxPhysics* gP, PxScene* gS, Vector3 _meanPos, Vector3 _meanVel);
	Vector3 velWidth, posWidth;
	Solids* addRigids();
	~GaussianSolidsGenerator();
	list<Solids*> getSolids() { return solids; };
};
class FireworkGenerator : public ParticleGenerator
{
protected:
	void FuegosCorazon(Vector3& newVel, float increase, Firework* parent, std::list<Firework*>& listParticles);
	void RandomFirework(Vector3& newVel, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles);
	void CircleFirework(Vector3& newVel, float increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles);
	void BatFirework(Vector3& newVel, float increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles);

	void CabezaBatFuegos(Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles);
	void FinAlasBatFuegos(Vector3& newVel, int x, Firework* parent, std::list<Firework*>& listParticles);
	void ParentesisBatFuegos(int x, Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles);
	void PicosAbajoBatFuegos(int x, Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles);
public:
	FireworkGenerator(Vector3 _meanPos, Vector3 _meanVel);
	list<Firework*> generateFireworks(Firework* parent);
	list<Particle*> generateParticles() override;
};
