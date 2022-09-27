#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos = {0,0,0}, Vector3 Vel = {0,0,0}, Vector3 acceleration = {0,0,0}, double dampling = 0.0);
	~Particle();
	void integrate(double t);
	Vector3 getPos();
	void setMass(double m) { mass = m; }
	void setVelocity(Vector3 v) { vel = v; }
	void setDamping(double d) { damp = d; }
	void setAcceleration(Vector3 a) { ac = a; }
	void setPosition(Vector3 p){ pose = physx::PxTransform(p.x, p.y, p.z); }
	void setRender(Vector4 color);
	//Vector3 getdir();
private:
	Vector3 vel;
	Vector3 ac;
	double damp;
	double mass;
	physx::PxTransform pose;
	RenderItem* renderItem;

};

