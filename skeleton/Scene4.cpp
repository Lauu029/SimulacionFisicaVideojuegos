#include "Scene4.h"

void Scene4::initScene()
{
	pS = new ParticleSystem(typeParticleSystem::SpringsGenerators);
}

void Scene4::updateScene(double t)
{
	pS->update(t);
}

void Scene4::keyPressed(unsigned char key)
{
	switch (tolower(key))
	{
	case'z':
		pS->GomaElastica();
		break;
	default:
		break;
	}
}
