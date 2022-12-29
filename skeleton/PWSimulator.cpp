#include "PWSimulator.h"

PWSimulator::PWSimulator(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	system = new SolidsSystem(gP, gS, typeSolidSystem::PowerWash);
}

PWSimulator::~PWSimulator()
{
	delete system;
}

void PWSimulator::initScene()
{
	system->initSystem();
}

void PWSimulator::updateScene(double t)
{
	system->update(t);
}

void PWSimulator::keyPressed(unsigned char key)
{
	system->keyPressed(key);
}
