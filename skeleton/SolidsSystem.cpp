#include "SolidsSystem.h"

SolidsSystem::SolidsSystem(PxPhysics* gPhysics, PxScene* gScene) {
	sP = gPhysics;
	sC = gScene;
	generator = new GaussianSolidsGenerator(sP, sC, { 0, 100, 0 }, { 0, 0, 0 });

}
void SolidsSystem::initSystem() {
	hsv color = { 25.0,0.73,0.7 };
	rgb col = hsv2rgb(color);
	//suelo
	floor = sP->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 500));
	floor->attachShape(*shape);
	item = new RenderItem(shape, floor, { col.r, col.g ,col.b, 1 });
	sC->addActor(*floor);
	//muro
	wall = sP->createRigidStatic(PxTransform(PxVec3(10, 10, -30)));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	wall->attachShape(*shape_suelo);
	color = { 154.0,0.73,0.7 };
	col = hsv2rgb(color);
	itemWall = new RenderItem(shape_suelo, wall, { col.r, col.g ,col.b,1 });
	sC->addActor(*wall);
}

void SolidsSystem::update(double t)
{
	if (generator->isActive())
	{
		if (numParticles < maxParticles) {
			solidParticles.push_back(generator->addRigids());
			numParticles++;
		}
	}
	for (int i = 0; i < solidParticles.size(); i++)
	{
		if (solidParticles[i]->time > 500)
			solidParticles[i]->kill();
		if (!solidParticles[i]->isAlive()) {
			sC->removeActor(*solidParticles[i]->getRigid());
			solidParticles.erase(solidParticles.begin() + i);
		}
		else solidParticles[i]->time++;
	}
}

SolidsSystem::~SolidsSystem()
{
	for (auto s : solidParticles)
	{
		sC->removeActor(*s->getRigid());
	}
	solidParticles.clear();
	if (generator != nullptr)
		delete generator;
	itemWall->release();
	item->release();
	sC->removeActor(*floor);
	sC->removeActor(*wall);
}
