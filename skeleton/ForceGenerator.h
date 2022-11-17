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
	~GravityGenerator() {};
	virtual void updateForce(Particle* p, double t) override;
	inline void setGravity(const Vector3& g) { gravity = g; };
private:
	Vector3 gravity;
};
class WindGenerator : public ForceGenerator {
public:
	WindGenerator(float r, Vector3 v, Vector3 p);
	~WindGenerator();
	virtual void updateForce(Particle* p, double t) override;
protected:
	bool checkDistance(Particle* p);
	float radius = 0;
	Particle* actionRate = nullptr;
	Vector3 pos;
	Vector3 vel;
};
class TorbellinoGenerator : public WindGenerator {
public:
	TorbellinoGenerator(float r, Vector3 v, Vector3 p);
	~TorbellinoGenerator(){};
	virtual void updateForce(Particle* p, double t) override;
};
class ExplosionGenerator : public ForceGenerator {
public:
	ExplosionGenerator();
	~ExplosionGenerator();
	virtual void updateForce(Particle* p, double t) override;
};