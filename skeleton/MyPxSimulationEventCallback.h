#pragma once
#include <PxSimulationEventCallback.h>
#include <PxPhysicsAPI.h>
#include <PxSimulationEventCallback.h>
#include "Solids.h"
using namespace physx;

class MyPxSimulationEventCallback : public PxSimulationEventCallback
{
public:
	//This is called when a breakable constraint breaks.
	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {};
	//This is called with the actors which have just been woken up.
	virtual void onWake(PxActor** actors, PxU32 count) override {};
	//This is called with the actors which have just been put to sleep.
	virtual void onSleep(PxActor** actors, PxU32 count) override {};
	//This is called when certain contact events occur.
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override {
		PxRigidActor* ac1 = pairHeader.actors[0];
		PxRigidActor* ac2 = pairHeader.actors[1];

		Solids* particle1 = (Solids*)ac1->userData;
		Solids* particle2 = (Solids*)ac2->userData;
		if (particle1 != nullptr && particle2 != nullptr) {
			if (particle1->getType().gst == Man1 && particle2->getType().gst == Dirt1)
				particle2->kill();
			if (particle2->getType().gst == Man1 && particle1->getType().gst == Dirt1)
				particle1->kill();
		}

	}
	//This is called with the current trigger pair events.
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override { };
	//Provides early access to the new pose of moving rigid bodies.
	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override {};
};

