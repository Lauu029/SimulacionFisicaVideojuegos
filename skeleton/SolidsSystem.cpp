#include "SolidsSystem.h"

SolidsSystem::SolidsSystem(PxPhysics* gPhysics, PxScene* gScene) {
	sP = gPhysics;
	sC = gScene;
	timeSinceLastAdding = 0;
	generator = new GaussianSolidsGenerator(sP, sC, { 0, 100, 0 }, { 0, 0, 0 });
	sFR = new SolidsForceRegistry();
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
	timeSinceLastAdding++;
	if (generator->isActive() && timeSinceLastAdding > 100)
	{
		if (numParticles < maxParticles) {
			solidParticles.push_back(generator->addRigids());
			if(wind!=nullptr)
				sFR->addRegistry(solidParticles.back(), wind);
			numParticles++;
			timeSinceLastAdding = 0;
		}
	}
	for (int i = 0; i < solidParticles.size(); i++)
	{
		if (!solidParticles[i]->isAlive()) {
			sC->removeActor(*solidParticles[i]->getRigid());
			sFR->deleteSolid(solidParticles[i]);
			delete solidParticles[i];
			solidParticles.erase(solidParticles.begin() + i);
			numParticles--;
		}
		else solidParticles[i]->update(t);
	}
	if (sFR != nullptr)
		sFR->updateForces(t);
}

SolidsSystem::~SolidsSystem()
{
	for (auto s : solidParticles)
	{
		sC->removeActor(*s->getRigid());
		delete s;
	}
	solidParticles.clear();
	if (generator != nullptr)
		delete generator;
	itemWall->release();
	item->release();
	sC->removeActor(*floor);
	sC->removeActor(*wall);
	if (wind != nullptr) {
		delete wind;
		wind = nullptr;
	}
	if (sFR != nullptr)
		delete sFR;
}
void SolidsSystem::addWind()
{
	if (wind == nullptr) wind = new SolidsWindGenerator(100, { -50,20,0 }, { 70,50,5 });
	for (auto p : solidParticles)
	{
		if (p!=nullptr)
			sFR->addRegistry(p, wind);
	}
}
void SolidsSystem::deleteWind()
{
	for (auto p : solidParticles)
	{
		sFR->deleteForce(wind);
	}
	delete wind;
	wind = nullptr;
}