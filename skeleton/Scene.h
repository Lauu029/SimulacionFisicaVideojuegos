#pragma once
#include "ParticleSystem.h"
#include <foundation/PxTransform.h>
#include "checkML.h"
#include "SolidsSystem.h"
using namespace physx;
class Scene
{
public:
	Scene(PxPhysics* gPhysics, PxScene* gScene) ;
	virtual ~Scene();
	virtual void initScene()=0;
	virtual void updateScene(double t)=0;
	virtual void keyPressed(unsigned char key)=0;
protected:
	vector<Particle*> sceneParticles;
	ParticleSystem* pS = nullptr;
	Particle* suelo = nullptr;
	PxPhysics* gP = nullptr;
	PxScene* gS = nullptr;
};

