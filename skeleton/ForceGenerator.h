#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	virtual void updateForce(Particle* p)=0;
	double t = -1e10;
	Particle* actionRate = nullptr;
};
class GravityGenerator :public ForceGenerator {
public:
	GravityGenerator(const Vector3& g);
	~GravityGenerator() {};
	virtual void updateForce(Particle* p) override;
	inline void setGravity(const Vector3& g) { gravity = g; };
private:
	Vector3 gravity;
};
class ParticleDragGenerator : public ForceGenerator {
public:
	ParticleDragGenerator(const float _k1, const float _k2);
	virtual void updateForce(Particle* particle) override;
	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; };
	inline float getk1() { return k1; };
	inline float getk2() { return k2; };
protected:
	float k1;
	float k2;
};
class WindGenerator : public ForceGenerator {
public:
	WindGenerator(float r, Vector3 v, Vector3 p);
	virtual ~WindGenerator();
	virtual void updateForce(Particle* p) override;
protected:
	bool checkDistance(Particle* p);
	float radius = 0;
	Vector3 pos;
	Vector3 vel;
};
class TorbellinoGenerator : public WindGenerator {
public:
	TorbellinoGenerator(float r, Vector3 v, Vector3 p);
	virtual ~TorbellinoGenerator();
	virtual void updateForce(Particle* p) override;
};
class ExplosionGenerator : public ForceGenerator {
public:
	ExplosionGenerator(float r, Vector3 p);
	virtual ~ExplosionGenerator();
	virtual void updateForce(Particle* p) override;
protected:
	float radius = 0;
	Vector3 meanPose;
};

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(double _k, double resting_Length, Particle* other);
	virtual void updateForce(Particle* p) override;
	inline void setK(double _k) { k = _k; };
	virtual ~SpringForceGenerator();
protected:
	double k;
	double restingLength;
	Particle* particle= nullptr;
};

//Muelle anclado a un punto fijo
class AnchoredSpringFG : public SpringForceGenerator {
public:
	AnchoredSpringFG(double _k, double _resting, const Vector3& anchor_pos);
	~AnchoredSpringFG() ;
private:
	Particle* ancla = nullptr;
};

class GomaElasticaGenerator : public SpringForceGenerator {
public:
	GomaElasticaGenerator(double _k, double resting_Length, Particle* other);
	~GomaElasticaGenerator(){};
	virtual void updateForce(Particle* p) override;
};

