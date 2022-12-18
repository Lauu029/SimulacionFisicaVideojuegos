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
	switch (key)
	{
	case'w':
		system->moveCharacter(Vector3(0, 0, -1000));
		break;
	case's':
		system->moveCharacter(Vector3(0, 0, 1000));
		break;
	case'a':
		system->moveCharacter(Vector3(-1000, 0, 0));
		break;
	case'd':
		system->moveCharacter(Vector3(1000, 0, 0));
		break;
	case ' ':
		system->moveCharacter(Vector3(0, 10000, 0));
		break;
		
	default:
		break;
	}
}
