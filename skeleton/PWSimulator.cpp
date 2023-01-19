#include "PWSimulator.h"

PWSimulator::PWSimulator(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	level = 1;
	pS = new ParticleSystem(typeParticleSystem::particleGenerators);
	contadorFuegos = 100000;
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
			clearLevel();
			level++;
		}
	}
	if (contadorFuegos > 0&& contadorFuegos<201) {
		if (contadorFuegos % 15 == 0)
			pS->generateFireworkSystem(FireworkType::random, { -50 + (float)(rand() % 100),0, -50 + (float)(rand() % 100) });
		if (contadorFuegos % 32 == 0)
			pS->generateFireworkSystem(FireworkType::heart, { -50 + (float)(rand() % 100),0, -50 + (float)(rand() % 100) });
		if (contadorFuegos % 78 == 0)
			pS->generateFireworkSystem(FireworkType::batFuego, { -50 + (float)(rand() % 100),0, -50 + (float)(rand() % 100) });
		if (contadorFuegos % 23 == 0)
			pS->generateFireworkSystem(FireworkType::circle, { -50 + (float)(rand() % 100),0, -50 + (float)(rand() % 100) });
		contadorFuegos--;
	}
	if (contadorFuegos <= 0 && pS->finishFireworks()) {
			changeLevel();
			shouldIChange = true;
			contadorFuegos = 10000;
		}
	if (pS != nullptr) {
		pS->update(t);
	}
}

void PWSimulator::keyPressed(unsigned char key)
{
	system->keyPressed(key);
	if (level == 3) {
		if (tolower(key) == 'q') {
			pS->addExplosion(GetCamera()->getEye());
		}
	}
}

void PWSimulator::clearLevel() {
	system->clearLevel();
	pS->ActivateNiebla(false);
	contadorFuegos = 200;
}

void PWSimulator::changeLevel() {
	switch (level)
	{
	case 2:
		system->createLevel2();
		break;
	case 3:
		system->createLevel3();
		pS->CreateLluvia(50);
		break;
	case 4:
		pS->addSlinky();
		break;
	default:
		break;
	}
}
