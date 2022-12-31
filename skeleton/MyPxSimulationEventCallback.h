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
			generalSolidType gst1 = particle1->getType().gst;
			generalSolidType gst2 = particle2->getType().gst;

			//borrado dirt 1
			if ((gst1 == Man1||gst1==Man3) && particle2->getType().gst == Dirt3)
				particle2->kill();
			if ((gst2== Man1||gst2==Man3) && particle1->getType().gst == Dirt3)
				particle1->kill();
			//borrado dirt 2
			if ((gst1 == Man3) && particle2->getType().gst == Dirt2)
				particle2->kill();
			if ((gst2 == Man3) && particle1->getType().gst == Dirt2)
				particle1->kill();
			//borrado dirt 3
			if ((gst1 == Man2) && particle2->getType().gst == Dirt1)
				particle2->kill();
			if ((gst2 == Man2) && particle1->getType().gst == Dirt1)
				particle1->kill();
		}

	}
	//This is called with the current trigger pair events.
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override { };
	//Provides early access to the new pose of moving rigid bodies.
	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override {};
};

