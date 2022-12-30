#include "SolidsSystem.h"

SolidsSystem::SolidsSystem(PxPhysics* _gPhysics, PxScene* _gScene, typeSolidSystem type) {
	gPhysics = _gPhysics;
	gScene = _gScene;
	timeSinceLastAdding = 0;
	sFR = new SolidsForceRegistry();
	t = type;
	cam = GetCamera();
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
	//Muro
	createDirtWall();
	//Personaje
	PxMaterial* mat;
	mat = gPhysics->createMaterial(0.5, 0.5, 0.1);
	PxRigidDynamic* newRigid = gPhysics->createRigidDynamic(PxTransform({ 0,2,0 }));

	mainCharacter = new Solids({ 0,10,0 }, { 0,0,0 },
		gPhysics->createShape(PxBoxGeometry(10, 10, 10), *mat), newRigid, PWSCharacter());
	mainCharacter->getRigid()->setMass(15);
	mainCharacter->getRigid()->setMassSpaceInertiaTensor(PxVec3(0.0f, 0.0f, 0.0f));
	mainCharacter->getRigid()->setAngularDamping(0.2);
	gScene->addActor(*newRigid);
	//Mangueras
	manguera1 = new UniformSolidsGenerator(gPhysics, gScene, { 0, 20, 100 }, { 20,0, 0 }, 10, Manguera1Features());
	manguera1->changeActive();
	manguera2 = new UniformSolidsGenerator(gPhysics, gScene, { 0, 20, 100 }, { 100,0, 0 }, 40, Manguera2Features());
	manguera3 = new UniformSolidsGenerator(gPhysics, gScene, { 0, 20, 100 }, { 1,0, 0 }, 10, Manguera3Features());
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
	if (manguera1 != nullptr) {
		Vector3 pos = cam->getTransform().p;
		if (manguera1->isActive())
		{
			manguera1->changePos({ pos.x, pos.y - 3, pos.z });
			manguera1->setVel(cam->getDir());
			if (solidParticles.size() < 100)
				solidParticles.push_back(manguera1->addRigids());
		}
	}
	if (manguera2 != nullptr) {
		Vector3 pos = cam->getTransform().p;
		if (manguera2->isActive())
		{
			manguera2->changePos({ pos.x, pos.y - 3, pos.z });
			manguera2->setVel(cam->getDir() * 10);
			if (solidParticles.size() < 100)
				solidParticles.push_back(manguera2->addRigids());
		}
	}
	if (manguera3 != nullptr) {
		Vector3 pos = cam->getTransform().p;
		if (manguera3->isActive())
		{
			manguera3->changePos({ pos.x, pos.y - 3, pos.z });
			manguera3->setVel(cam->getDir() * 0.5);
			if (solidParticles.size() < 100)
				solidParticles.push_back(manguera3->addRigids());
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
		Vector3 playerPos = mainCharacter->getPos();
		//cam->setEye({ playerPos.x+10, playerPos.y + 10.0f, playerPos.z });
	}
}

void SolidsSystem::changeFontActive(int numFuente, bool act)
{
	switch (numFuente)
	{
	case 1:
		manguera1->setActive(act);
		break;
	case 2:
		manguera2->setActive(act);
		break;
	case 3:
		manguera3->setActive(act);
		break;
	default:
		break;
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
	for (auto d : dirt) {
		gScene->removeActor(*d->getRigid());
		delete d;
	}
	dirt.clear();
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
	if (manguera1 != nullptr)
		delete manguera1;
	if (manguera2 != nullptr)
		delete manguera2;
	if (manguera3 != nullptr)
		delete manguera3;
	if (Suciedades != nullptr)
		delete Suciedades;
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
void SolidsSystem::changeWaterVel(bool inc)
{
	manguera1->changeVel(inc);
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
void SolidsSystem::keyPressed(unsigned char key) {
	switch (key)
	{
	case 'W':
	{
		PxVec3 mDir = cam->getDir();
		PxVec3 force(mDir.x * 2.0f * 100, 0.0f, mDir.z * 2.0f * 100);
		mainCharacter->addForce(force);
		break;
	}
	case 'S':
	{
		PxVec3 mDir = cam->getDir();
		PxVec3 force(mDir.x * 2.0f * 100, 0.0f, mDir.z * 2.0f * 100);
		mainCharacter->addForce(-force);
		break;
	}
	case 'A':
	{
		PxVec3 mDir = cam->getDir();
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		PxVec3 force(viewY.x * 2.0f * 100, 0.0f, viewY.z * 2.0f * 100);
		mainCharacter->addForce(-force);
		break;
	}
	case 'D':
	{
		PxVec3 mDir = cam->getDir();
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		PxVec3 force(viewY.x * 2.0f * 100, 0.0f, viewY.z * 2.0f * 100);
		mainCharacter->addForce(force);
		break;
	}
	case ' ':
		moveCharacter(Vector3(0, 10000, 0));
		break;
	case 'z':
		changeFontActive(1, !manguera1->isActive());
		changeFontActive(2, false);
		changeFontActive(3, false);
		break;
	case 'x':
		changeFontActive(2, !manguera2->isActive());
		changeFontActive(1, false);
		changeFontActive(3, false);
		break;
	case 'c':
		changeFontActive(3, !manguera3->isActive());
		changeFontActive(2, false);
		changeFontActive(1, false);
		break;
	case'o':
		manguera1->changeVel(false);
		break;
	case'p':
		manguera1->changeVel(true);
		break;
	default:
		break;
	}
}
void SolidsSystem::createDirtWall() {
	//Muro
	wall = gPhysics->createRigidStatic(PxTransform(PxVec3(10, 10,50)));
	PxShape* shape = CreateShape(PxBoxGeometry(40, 20, 5));
	wall->attachShape(*shape);
	hsv color = { 154.0,0.73,0.7 };
	rgb col = hsv2rgb(color);
	itemWall = new RenderItem(shape, wall, { col.r, col.g ,col.b,1 });
	gScene->addActor(*wall);

	//suciedad
	Suciedades = new UniformSolidsGenerator(gPhysics, gScene,
		{ 10, 10, 55 }, { 0,0, 0 }, 10, Type1Dirt(),40,20,0);
	for (int i = 0; i < 500; i++)
	{
		Solids* d = Suciedades->addRigids();
		d->getRigid()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		dirt.push_back(d);
	}

}