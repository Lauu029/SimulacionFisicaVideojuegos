#include "Scene3.h"

void Scene3::initScene()
{
	pS = new ParticleSystem(typeParticleSystem::ForceGenerators);
}

void Scene3::updateScene(double t)
{
	pS->update(t);
}

void Scene3::keyPressed(unsigned char key)
{
	switch (tolower(key))
	{
	case 'z':
		pS->addGravity();
		break;
	case 'x':
		pS->addWind();
		break;
	case 'c':
		pS->addTorbellino();
		break;
	case 'v':
		pS->addExplosion();
		break;
	case 'p':
		pS->GenerateForceParticles(type_gravity);
		break;
	case 'o':
		pS->GenerateForceParticles(type_wind);
		break;
	case 'i':
		pS->GenerateForceParticles(type_torbellino);
		break;
	case 'u':
		pS->GenerateForceParticles(type_explosion);
		break;
	default:
		break;
	}
}
