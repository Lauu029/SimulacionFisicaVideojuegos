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

	void integrate(float t);
	
	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { ac = a; }
	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); }
	void setRender(particleShape s, Vector3 size, Vector4 color);
	void setColor(Vector4 _color);
	void setMass(float m) { mass = m; };
	void setDampling(float d) { damp = d; };

	Vector3 getPos();
	Vector3 getVel() { return vel; };
	Vector3 getAcceleration() { return ac; }
	float getDamping() { return damp; }
	float getRemainingTime() { return remainingTime; }
	Vector3 getSize() { return size; }
	Vector4 getColor() { return renderItem->color; }
	particleType getParticleType() { return type; };
	float getInvMass() { return inverse_mass; };
	float getMass() { return mass; };

	void clearForce() { force *= 0; };
	void addForce(const Vector3& f) { force += f; };
protected:
	Vector3 force;
	Vector3 vel;
	Vector3 ac;
	float damp;
	float mass;
	float inverse_mass;
	float remainingTime;
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
