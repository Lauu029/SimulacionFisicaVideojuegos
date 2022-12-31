#include "Scene2.h"

void Scene2::initScene()
{
	pS = new ParticleSystem(typeParticleSystem::particleGenerators);
	suelo = new Particle(Suelo(), true);
}

void Scene2::updateScene(double t)
{
	pS->update(t);
}

void Scene2::keyPressed(unsigned char key)
{
	switch (tolower(key))
	{
	case 'z':
		pS->generateFireworkSystem(FireworkType::heart, { 0.0 ,0.0, 150.0 });
		break;
	case 'x':
		pS->generateFireworkSystem(FireworkType::random, { 0.0 ,0.0, 100.0 });
		break;
	case 'c':
		pS->generateFireworkSystem(FireworkType::circle, { 0.0 ,0.0, 100.0 });
		break;
	case 'v':
		pS->generateFireworkSystem(FireworkType::batFuego, { 0.0 ,0.0, 100.0 });
		break;
	case 'b':
			pS->getParticleGenerator(typeParticleGenerator::font)->changeActive();
		break;
	case 'n':
			pS->getParticleGenerator(typeParticleGenerator::fog)->changeActive();
		break;
	default:
		break;
	}
}
