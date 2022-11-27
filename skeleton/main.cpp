#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "ParticleSystem.h"
#include "ParticleType.h"
#include "checkML.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

physx::PxTransform floorPose = { 0,0,0 };
Scene* mainScene = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	srand(time(NULL));   

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	gScene = gPhysics->createScene(sceneDesc);
	mainScene = new Scene4 ();
	mainScene->initScene(); 
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	if (mainScene != nullptr)
		mainScene->updateScene(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	if (mainScene != nullptr)
		delete mainScene;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	Vector3 pos = GetCamera()->getTransform().p;
	if (mainScene != nullptr)
		mainScene->keyPressed(key);  
	switch (tolower(key))
	{
		//Escena proyectiles
	case '0':
		if (mainScene != nullptr) {
			delete mainScene;
			mainScene = nullptr;
		}
		mainScene = new Scene1();
		mainScene->initScene();
		break;
		//Escena generadores partículas
	case '1':
		if (mainScene != nullptr) {
			delete mainScene;
			mainScene = nullptr;
		}
		mainScene = new Scene2();
		mainScene->initScene();
		break;
		//Escena fuerzas
	case '2':
		if (mainScene != nullptr) {
			delete mainScene;
			mainScene = nullptr;
		}
		mainScene = new Scene3();
		mainScene->initScene();
		break;
	case '3':
		if (mainScene != nullptr) {
			delete mainScene;
			mainScene = nullptr;
		}
		mainScene = new Scene4();
		mainScene->initScene();
		break; 
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}