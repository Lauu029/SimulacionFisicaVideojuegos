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
		pS->generateFireworkSystem(FireworkType::heart);
		break;
	case 'x':
		pS->generateFireworkSystem(FireworkType::random);
		break;
	case 'c':
		pS->generateFireworkSystem(FireworkType::circle);
		break;
	case 'v':
		pS->generateFireworkSystem(FireworkType::batFuego);
		break;
	case 'b':
			pS->getParticleGenerator(typeParticleGenerator::font)->setActive();
		break;
	case 'n':
			pS->getParticleGenerator(typeParticleGenerator::fog)->setActive();
		break;
	default:
		break;
	}
}
