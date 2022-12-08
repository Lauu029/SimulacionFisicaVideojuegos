#include "Scene5.h"


Scene5::Scene5(PxPhysics* gPhysics, PxScene* gScene) : Scene(gPhysics, gScene)
{
	hsv color = { 25.0,0.73,0.7 };
	rgb col = hsv2rgb(color);
	//suelo
	floor = gP->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 500));
	floor->attachShape(*shape);
	item = new RenderItem(shape, floor, { col.r, col.g ,col.b, 1 });
	gS->addActor(*floor);
	//muro
	wall = gP->createRigidStatic(PxTransform(PxVec3(10, 10, -30)));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	wall->attachShape(*shape_suelo);
	color = { 154.0,0.73,0.7 };
	col = hsv2rgb(color);
	itemWall = new RenderItem(shape_suelo, wall, { col.r, col.g ,col.b,1 });
	gS->addActor(*wall);

	generator = new GaussianSolidsGenerator(gP, gS, { 0, 100, 0 }, { 0, 0, 0 });

}

Scene5::~Scene5()
{
	itemWall->release();
	item->release();
	gS->removeActor(*floor);
	gS->removeActor(*wall);
	for (auto g : particles)
	{
		gS->removeActor(*g);
	}
	floor = nullptr;
}

void Scene5::initScene()
{
	for (int i = 0; i < 3; i++)
	{

	generator->addRigids();
	}

}

void Scene5::updateScene(double t)
{
	if (generator->isActive())
	{
		if (numParticles < maxParticles) {
			numParticles++;
		}
	}
}

void Scene5::keyPressed(unsigned char key)
{
	switch (tolower(key))
	{
	case'z':
		generator->setActive();
		break;
	default:
		break;
	}
}
