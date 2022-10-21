#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "ParticleType.h"
#include <list>
#include <random>

class Particle
{
public:
	Particle(particleType p);
	~Particle();

	void integrate(double t);

	void setMass(double m) { mass = m; }
	void setVelocity(Vector3 v) { vel = v; }
	void setDamping(double d) { damp = d; }
	void setAcceleration(Vector3 a) { ac = a; }
	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); }
	void setRender(particleShape s, Vector3 size, Vector4 color);
	void setColor(Vector4 _color);

	Vector3 getPos();
	Vector3 getAcceleration() { return ac; }
	double getDamping() { return damp; }
	double getRemainingTime() { return remainingTime; }
	Vector3 getSize() { return size; }
	Vector4 getColor() { return renderItem->color; }
	particleType getParticleType() { return type; };
protected:
	Vector3 vel;
	Vector3 ac;
	double damp;
	double mass;
	double remainingTime;
	physx::PxTransform pose;
	RenderItem* renderItem;

	particleType type;
	particleShape shape;
	Vector3 size;
	Vector4 color;
};

class Firework : public Particle {
public:
	Firework(particleType p,int nH);
	std::list<Firework*> explode();
protected:
	std::default_random_engine ran;
	std::normal_distribution<> dist{ 0.5, 0.5 };
	int numHijos;
};
