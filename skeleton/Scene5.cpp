#include "Scene5.h"


Scene5::Scene5(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	system = new SolidsSystem(gPhysics, gScene, typeSolidSystem::NormalSolids);
}

Scene5::~Scene5()
{
	delete system;
}

void Scene5::initScene()
{
	system->initSystem();
}

void Scene5::updateScene(double t)
{
	system->update(t);
}

void Scene5::keyPressed(unsigned char key)
{
	switch (tolower(key))
	{
	case'z':
		system->getGen()->changeActive();
		break;
	case'x':
		system->addWind();
		break;
	case'c':
		system->deleteWind();
		break;
	default:
		break;
	}
}
