#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "ParticleType.h"
#include <list>
#include <random>

enum FireworkType { heart, random, circle, batFuego };

class Particle
{
public:
	Particle(particleType p, bool b);
	~Particle();

	void integrate(double t);
	
	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { ac = a; }
	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); }
	void setRender(particleShape s, Vector3 size, Vector4 color);
	void setColor(Vector4 _color);

	Vector3 getPos();
	Vector3 getVel() { return vel; };
	Vector3 getAcceleration() { return ac; }
	double getDamping() { return damp; }
	double getRemainingTime() { return remainingTime; }
	Vector3 getSize() { return size; }
	Vector4 getColor() { return renderItem->color; }
	particleType getParticleType() { return type; };
	double getMass() { return mass; };

	void clearForce() { force *= 0; };
	void addForce(const Vector3& f) { force += f; };
protected:
	Vector3 force;
	Vector3 vel;
	Vector3 ac;
	double damp;
	double mass;
	double inverse_mass;
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
	Firework(particleType p,int nH, FireworkType _t, bool b);
	void explode();
	bool isActive() { return _isActive; };
	int getNumHijos() { return numHijos; };
	FireworkType type() { return t;  }
protected:
	int numHijos;
	bool _isActive;
	FireworkType t;
};
