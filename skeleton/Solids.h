#pragma once

#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "checkML.h"
#include "SolidType.h"

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
	SolidType type;
	generalSolidType gst = General;
public:
	Solids(Vector3 _meanPos, Vector3 _meanVel, PxShape* _gShape, PxRigidDynamic* rig, SolidType _t);
	void update(double t);
	void kill() { alive = false; };
	bool isAlive() { return alive; };
	PxRigidDynamic* getRigid() { return rigid; };
	void addForce(Vector3 f) { force += f; };
	Vector3 getPos() { return rigid->getGlobalPose().p; };
	Vector3 getVel() { return rigid->getLinearVelocity(); };
	void move(Vector3 v);
	void setMass(float m) { rigid->setMass(m); };
	void setDir(Vector3 dir) { rigid->addTorque(dir); };
	~Solids();
};

