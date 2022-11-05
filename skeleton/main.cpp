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

ParticleSystem* partSysFireworks = nullptr;
ParticleSystem* partSysGravity = nullptr;
physx::PxTransform floorPose = { 0,0,0 };
vector <Particle*> sceneParticles;

Particle* suelo_ = nullptr;
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

	suelo_ = new Particle(Suelo(), true);
	gScene = gPhysics->createScene(sceneDesc);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	for (int i = 0; i < sceneParticles.size(); i++)
	{
		if (sceneParticles[i]->getPos().y < 0 || sceneParticles[i]->getRemainingTime() < 0) {
			delete sceneParticles[i];
			sceneParticles[i] = nullptr;
			sceneParticles.erase(sceneParticles.begin() + i);
		}
		else
			sceneParticles[i]->integrate(t);

	}
	if (partSysFireworks != nullptr)
		partSysFireworks->update(0.5);
	if (partSysGravity != nullptr)
		partSysGravity->update(0.5);
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	if (partSysFireworks != nullptr) {
		delete partSysFireworks;
		partSysFireworks = nullptr;
	}
	if (partSysGravity != nullptr) {
		delete partSysGravity;
		partSysGravity = nullptr;
	}
	for (auto s : sceneParticles)
		delete s;

	delete suelo_;
	sceneParticles.clear();
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
	switch (tolower(key))
	{
	case '1':
		if (partSysGravity != nullptr) delete partSysGravity; partSysGravity = nullptr;
		if (partSysFireworks == nullptr)
			partSysFireworks = new ParticleSystem(typeParticleSystem::particleGenerators);
		break;
	case '2':
		if (partSysFireworks != nullptr) delete partSysFireworks; partSysFireworks = nullptr;
		if (partSysGravity == nullptr)
			partSysGravity = new ParticleSystem(typeParticleSystem::ForceGenerators);
		break;
	case 'm':
		if (partSysGravity != nullptr)
			partSysGravity->addGravity();
		break;
	case'n':
		if (partSysGravity != nullptr)
			partSysGravity->deleteGravity();
		break;
	case 'b':
		if (partSysGravity != nullptr)
			partSysGravity->ParticlesGravitySystem();
		break;
	case 'p':
		if (partSysFireworks != nullptr)
			partSysFireworks->getParticleGenerator(typeParticleGenerator::font)->setActive();
		break;
	case 'o':
		if (partSysFireworks != nullptr)
			partSysFireworks->getParticleGenerator(typeParticleGenerator::fog)->setActive();
		break;
	case 'z':

		sceneParticles.push_back(new Particle(Pistol(GetCamera()->getDir(), pos,100), true));
		break;
	case 'x':
		sceneParticles.push_back(new Particle(Artillery(GetCamera()->getDir(), pos,100), true));
		break;
	case 'c':
		sceneParticles.push_back(new Particle(Fireball(GetCamera()->getDir(), pos,100), true));
		break;
	case 'v':
		sceneParticles.push_back(new Particle(Laser(GetCamera()->getDir(), pos,100), true));
		break;
	case'h':
		if (partSysFireworks != nullptr)
			partSysFireworks->generateFireworkSystem(FireworkType::heart);
		break;
	case 'j':
		if (partSysFireworks != nullptr)
			partSysFireworks->generateFireworkSystem(FireworkType::random);
		break;
	case'k':
		if (partSysFireworks != nullptr)
			partSysFireworks->generateFireworkSystem(FireworkType::circle);
		break;
	case 'l':
		if (partSysFireworks != nullptr)
			partSysFireworks->generateFireworkSystem(FireworkType::batFuego);
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