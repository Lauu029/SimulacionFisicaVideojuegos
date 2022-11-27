#pragma once
#include "ParticleSystem.h"
#include <foundation/PxTransform.h>
using namespace physx;
class Scene
{
public:
	Scene() {};
	~Scene();
	virtual void initScene()=0;
	virtual void updateScene(double t)=0;
	virtual void keyPressed(unsigned char key)=0;
protected:
	vector<Particle*> sceneParticles;
	ParticleSystem* pS = nullptr;
	Particle* suelo = nullptr;

};

