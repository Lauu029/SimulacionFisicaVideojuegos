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
	case'x':
		pS->addMasa();
		break;
	case'c':
		pS->quitaMasa();
		break;
	case'v':
		pS->changeLiquid(l1);
		break;
	case'b':
		pS->changeLiquid(l2);
		break;
	case'n':
		pS->changeLiquid(l3);
		break;
	default:
		break;
	}
}