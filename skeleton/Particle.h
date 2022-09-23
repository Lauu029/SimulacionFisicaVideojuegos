#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acceleration, double dampling);
	~Particle();
	void integrate(double t);
	Vector3 getPos();
	//Vector3 getdir();
private:
	Vector3 vel;
	Vector3 ac;
	double damp;
	physx::PxTransform pose;
	RenderItem* renderItem;

};

