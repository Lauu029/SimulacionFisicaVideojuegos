#pragma once

#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "checkML.h"

using namespace physx;
class Solids
{
protected:
	Vector3 pos, vel;
	PxRigidDynamic* rigid = nullptr;
	RenderItem* item = nullptr;
	PxShape* gShape = nullptr;
	Vector4 color;
	bool alive = true;
	Vector3 size;
	int time;
	Vector3 force;
public:
	Solids(Vector3 _meanPos, Vector3 _meanVel,Vector4 col, Vector3 s,
	 PxShape* _gShape, PxRigidDynamic* rig);
	void update(double t);
	void kill() { alive = false; };
	bool isAlive() { return alive; };
	PxRigidDynamic* getRigid() { return rigid; };
	void addForce(Vector3 f) { force += f; };
	Vector3 getPos() { return rigid->getGlobalPose().p; };
	Vector3 getVel() { return rigid->getLinearVelocity(); };
	~Solids();
};

