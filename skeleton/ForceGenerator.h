#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, float t)=0;
	Particle* actionRate = nullptr;
};
class GravityGenerator :public ForceGenerator {
public:
	GravityGenerator(const Vector3& g);
	~GravityGenerator() {};
	virtual void updateForce(Particle* p, float t) override;
	inline void setGravity(const Vector3& g) { gravity = g; };
private:
	Vector3 gravity;
};
class ParticleDragGenerator : public ForceGenerator {
public:
	ParticleDragGenerator(const float _k1, const float _k2);
	virtual void updateForce(Particle* particle, float t) override;
	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; };
	inline float getk1() { return k1; };
	inline float getk2() { return k2; };
	void setk(float k) { k1 = k; };
protected:
	float k1;
	float k2;
};
class WindGenerator : public ForceGenerator {
public:
	WindGenerator(float r, Vector3 v, Vector3 p);
	virtual ~WindGenerator();
	virtual void updateForce(Particle* p, float t) override;
	void changeWindForce(Vector3 v) { vel = v; };
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
	virtual void updateForce(Particle* p, float t) override;
};
class ExplosionGenerator : public ForceGenerator {
public:
	ExplosionGenerator(float r, Vector3 p);
	virtual ~ExplosionGenerator();
	virtual void updateForce(Particle* p, float t) override;
protected:
	float radius = 0;
	float t = -1e10;
	Vector3 meanPose;
};

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(float _k, float resting_Length, Particle* other);
	virtual void updateForce(Particle* p, float t) override;
	inline void setK(float _k) { k = _k; };
	virtual ~SpringForceGenerator();
protected:
	float k;
	float restingLength;
	Particle* particle= nullptr;
};

//Muelle anclado a un punto fijo
class AnchoredSpringFG : public SpringForceGenerator {
public:
	AnchoredSpringFG(float _k, float _resting, const Vector3& anchor_pos);
	~AnchoredSpringFG() ;
private:
	Particle* ancla = nullptr;
};

class GomaElasticaGenerator : public SpringForceGenerator {
public:
	GomaElasticaGenerator( float _k, float resting_Length, Particle* other);
	~GomaElasticaGenerator(){};
	virtual void updateForce(Particle* p, float t) override;
};
enum liquidType{l1,l2,l3};
class BuoyancyForceGenerator : public ForceGenerator {
public:
	BuoyancyForceGenerator(float mD, float h, float V, float d, Vector3 pos);
	virtual void updateForce(Particle* p, float t)override;
	virtual ~BuoyancyForceGenerator();
	void changeLiquid(liquidType l);
protected:
	float height;
	float volume;
	float liquidDensity;
	float maxDepth;
	float gravity =9.8;
	Particle* liquid = nullptr;
	hsv col;
	rgb rgb;
};