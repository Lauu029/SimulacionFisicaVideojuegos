#include "Scene5.h"


Scene5::Scene5(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	floor = gP->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1,500));
	floor->attachShape(*shape);
	item = new RenderItem(shape, floor, { 1.0, 0.3 ,0.8,1 });
	gS->addActor(*floor);
}

Scene5::~Scene5()
{
	gS->removeActor(*floor);
	floor->release();
}

void Scene5::initScene()
{
}

void Scene5::updateScene(double t)
{
}

void Scene5::keyPressed(unsigned char key)
{
}
