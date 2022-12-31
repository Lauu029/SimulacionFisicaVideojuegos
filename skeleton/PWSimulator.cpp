#include "PWSimulator.h"

PWSimulator::PWSimulator(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	level = 1;
	pS = new ParticleSystem(typeParticleSystem::particleGenerators);
	contadorFuegos = -1;
}

PWSimulator::~PWSimulator()
{
	if (system != nullptr)
		delete system;
}

void PWSimulator::initScene()
{
	system = new SolidsSystem(gP, gS, typeSolidSystem::PowerWash);
	system->initSystem();
}

void PWSimulator::updateScene(double t)
{
	if (system != nullptr) {
		system->update(t);
		if (system->getDirtAmount() <= 0 && shouldIChange) {
			shouldIChange = false;
			changeLevel();
			level++;
		}
	}
	if (contadorFuegos >= 0) {
		if (contadorFuegos % 15 == 0)
			pS->generateFireworkSystem(FireworkType::random, { (float)(rand() % 100),0,(float)(rand() % 100) });
		if (contadorFuegos % 32 == 0)
			pS->generateFireworkSystem(FireworkType::heart, { (float)(rand() % 100),0,(float)(rand() % 100) });
		if (contadorFuegos % 78 == 0)
			pS->generateFireworkSystem(FireworkType::batFuego, { (float)(rand() % 100),0,(float)(rand() % 100) });
		if (contadorFuegos % 23 == 0)
			pS->generateFireworkSystem(FireworkType::circle, { (float)(rand() % 100),0,(float)(rand() % 100) });
		contadorFuegos--;
		if (contadorFuegos == 0)
			changeLevel();
	}
	if (pS != nullptr) {
		pS->update(t);
	}
}

void PWSimulator::keyPressed(unsigned char key)
{
	system->keyPressed(key);
}

void PWSimulator::clearLevel() {
	system->clearLevel();
	contadorFuegos = 200;
}

void PWSimulator::changeLevel() {
	switch (level)
	{
	case 2:
		system->createLevel2();
		break;
	default:
		break;
	}
}
