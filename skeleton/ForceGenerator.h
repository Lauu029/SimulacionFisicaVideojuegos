#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, double t)=0;
	std::string name;
	double t = -1e10;
};
class GravityGenerator :public ForceGenerator {
public:
	GravityGenerator(const Vector3& g);
	~GravityGenerator();
	virtual void updateForce(Particle* p, double t) override;
	inline void setGravity(const Vector3& g) { gravity = g; };
private:
	Vector3 gravity;
};
class WindGenerator : public ForceGenerator {
public:
	WindGenerator();
	~WindGenerator();
	virtual void updateForce(Particle* p, double t) override;
};
class TorbellinoGenerator : public ForceGenerator {
public:
	TorbellinoGenerator();
	~TorbellinoGenerator();
	virtual void updateForce(Particle* p, double t) override;
};
class ExplosionGenerator : public ForceGenerator {
public:
	ExplosionGenerator();
	~ExplosionGenerator();
	virtual void updateForce(Particle* p, double t) override;
};