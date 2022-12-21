#include "SolidsSystem.h"

SolidsSystem::SolidsSystem(PxPhysics* _gPhysics, PxScene* _gScene, typeSolidSystem type) {
	gPhysics = _gPhysics;
	gScene = _gScene;
	timeSinceLastAdding = 0;
	sFR = new SolidsForceRegistry();
	t = type;
}
void SolidsSystem::initSystem() {

	switch (t)
	{
	case PowerWash:
		createPWSystem();
		break;
	case NormalSolids:
		CreateNormalSystem();
		break;
	default:
		break;
	}
}

void SolidsSystem::CreateNormalSystem()
{
	generator = new GaussianSolidsGenerator(gPhysics, gScene, { 0, 100, 0 }, { 0, 0, 0 });
	hsv color = { 25.0,0.73,0.7 };
	rgb col = hsv2rgb(color);
	//suelo
	floor = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 500));
	floor->attachShape(*shape);
	item = new RenderItem(shape, floor, { col.r, col.g ,col.b, 1 });
	gScene->addActor(*floor);
	//muro
	wall = gPhysics->createRigidStatic(PxTransform(PxVec3(10, 10, -30)));
	shape = CreateShape(PxBoxGeometry(40, 20, 5));
	wall->attachShape(*shape);
	color = { 154.0,0.73,0.7 };
	col = hsv2rgb(color);
	itemWall = new RenderItem(shape, wall, { col.r, col.g ,col.b,1 });
	gScene->addActor(*wall);
}

void SolidsSystem::createPWSystem()
{
	hsv color = { 55.0,0.73,0.7 };
	rgb col = hsv2rgb(color);
	//suelo
	floor = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 500));
	floor->attachShape(*shape);
	item = new RenderItem(shape, floor, { col.r, col.g ,col.b, 1 });
	gScene->addActor(*floor);
	//Personaje
	color = { 150.0, 0.8, 0.9 };
	col = hsv2rgb(color);
	PxMaterial* mat;
	mat = gPhysics->createMaterial(0.5, 0.5, 0.1);
	PxRigidDynamic* newRigid = gPhysics->createRigidDynamic(PxTransform({ 0,10,0 }));
	mainCharacter = new Solids({ 0,10,0 }, { 0,0,0 }, { col.r,col.g,col.b,1.0 }, { 10,10,10 },
		gPhysics->createShape(PxBoxGeometry(10, 10, 10), *mat), newRigid);
	mainCharacter->getRigid()->setMass(15);
	mainCharacter->getRigid()->setMassSpaceInertiaTensor(PxVec3(0.0f, 0.0f, 0.0f));
	gScene->addActor(*newRigid);
	//Manguera
	manguera = new UniformSolidsGenerator(gPhysics, gScene, { 0, 0, 100 }, { 200,0,0 }, 10);
	manguera->setActive();
	//mainCharacter->getRigid()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//mainCharacter->setMass(10);
}

void SolidsSystem::update(double t)
{
	if (generator != nullptr) {

		timeSinceLastAdding++;
		if (generator->isActive() && timeSinceLastAdding > 100)
		{
			if (numParticles < maxParticles) {
				solidParticles.push_back(generator->addRigids());
				if (wind != nullptr)
					sFR->addRegistry(solidParticles.back(), wind);
				numParticles++;
				timeSinceLastAdding = 0;
			}
		}
	}
	if (manguera != nullptr) {
		Vector3 pos = GetCamera()->getTransform().p;
		//manguera->changePos({20+ pos.x, pos.y, pos.z });
		//manguera->changePos({ pos.x, pos.y - 10, pos.z });
		//manguera->changeDir(GetCamera()->getDir());
		if (manguera->isActive())
		{
			if(solidParticles.size()<100)
			solidParticles.push_back(manguera->addRigids());
		}
	}
	for (int i = 0; i < solidParticles.size(); i++)
	{
		if (!solidParticles[i]->isAlive()) {
			gScene->removeActor(*solidParticles[i]->getRigid());
			sFR->deleteSolid(solidParticles[i]);
			delete solidParticles[i];
			solidParticles.erase(solidParticles.begin() + i);
			numParticles--;
		}
		else solidParticles[i]->update(t);
	}
	if (sFR != nullptr)
		sFR->updateForces(t);
	if (mainCharacter != nullptr) {
		//GetCamera()->setEye(mainCharacter->getPos() + Vector3(200, 0, 0));

	}
}

SolidsSystem::~SolidsSystem()
{
	for (auto s : solidParticles)
	{
		gScene->removeActor(*s->getRigid());
		delete s;
	}
	solidParticles.clear();
	if (generator != nullptr)
		delete generator;
	if (itemWall != nullptr)
		itemWall->release();
	if (item != nullptr)
		item->release();
	if (floor != nullptr)
		gScene->removeActor(*floor);
	if (wall != nullptr)
		gScene->removeActor(*wall);
	if (wind != nullptr) {
		delete wind;
		wind = nullptr;
	}
	if (sFR != nullptr)
		delete sFR;
	if (mainCharacter != nullptr)
		delete mainCharacter;
}
void SolidsSystem::addWind()
{
	if (wind == nullptr) wind = new SolidsWindGenerator(100, { -50,20,0 }, { 70,50,5 });
	for (auto p : solidParticles)
	{
		if (p != nullptr)
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

void SolidsSystem::moveCharacter(Vector3 dir)
{
	mainCharacter->move(dir);
}
