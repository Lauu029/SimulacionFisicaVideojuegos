#include "PWSimulator.h"

PWSimulator::PWSimulator(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	level = 1;
	pS = new ParticleSystem(typeParticleSystem::particleGenerators);
	contadorFuegos = 100;
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
		if (system->getDirtAmount() <= 0) changeLevel();
	}
	else if(contadorFuegos>=0) {
		if (contadorFuegos % 5 == 0)
			pS->generateFireworkSystem(FireworkType::random);
		contadorFuegos--;
	}
	if (pS != nullptr) {
		pS->update(t);
	}
}

void PWSimulator::keyPressed(unsigned char key)
{
	system->keyPressed(key);
}

void PWSimulator::changeLevel() {
	delete system;
	system = nullptr;
	GetCamera()->setEye(PxVec3(0.0f, 40.0f, 250.0f));
	GetCamera()->setDir(PxVec3(-0.5f, -0.2f, -30.0f));
	contadorFuegos = 100;
}
