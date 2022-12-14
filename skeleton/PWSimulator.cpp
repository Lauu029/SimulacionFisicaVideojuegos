#include "PWSimulator.h"

PWSimulator::PWSimulator(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics,gScene)
{
	system = new SolidsSystem(gP, gS);
}

PWSimulator::~PWSimulator()
{
	if (system != nullptr)
		delete system;
}

void PWSimulator::initScene()
{
	
}

void PWSimulator::updateScene(double t)
{
}

void PWSimulator::keyPressed(unsigned char key)
{
}
