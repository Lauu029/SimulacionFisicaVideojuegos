#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
enum particleType { Sphere, box, capsule };
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acceleration, double dampling, 
		particleType t, Vector3 size, Vector4 color, double time);
	~Particle();
	void integrate(double t);
	Vector3 getPos();
	void setMass(double m) { mass = m; }
	void setVelocity(Vector3 v) { vel = v; }
	void setDamping(double d) { damp = d; }
	void setAcceleration(Vector3 a) { ac = a; }
	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); }
	void setRender(particleType t, Vector3 size, Vector4 color);
	Vector3 getAcceleration() { return ac; }
	double getDamping() { return damp; }
	double getRemainingTime() { return remainingTime; }
	particleType getParticleType() { return type; }
	Vector3 getSize() { return size; }
	Vector4 getColor() { return renderItem->color; }
	void setColor(Vector4 _color);
private:
	Vector3 vel;
	Vector3 ac;
	double damp;
	double mass;
	double remainingTime;
	physx::PxTransform pose;
	RenderItem* renderItem;

	particleType type;
	Vector3 size;
	Vector4 color;

};

