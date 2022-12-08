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
	PxReal size;
public:
	int time;
	Solids(Vector3 _meanPos, Vector3 _meanVel,Vector4 col, PxReal s,
	 PxShape* _gShape, PxRigidDynamic* rig);
	
	void kill() { alive = false; };
	bool isAlive() { return alive; };
	PxRigidDynamic* getRigid() { return rigid; };
	~Solids();
};

