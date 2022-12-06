#include "Scene.h"

Scene::Scene(PxPhysics* gPhysics, PxScene* gScene)
{
	 gP = gPhysics;
	 gS = gScene; 
}

Scene::~Scene()
{
	for (auto p : sceneParticles)
		delete p;
	sceneParticles.clear();
	if (pS != nullptr)
		delete pS;
	if (suelo != nullptr)
		delete suelo;
}
