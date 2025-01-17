#include "ParticleGenerator.h"
//Generadores de part�culas
UniformParticleGenerator::UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel, int n, bool m, int s)
{
	meanPos = _meanPos;
	meanVel = _meanVel;
	numParticles = n;
	move = m;
	sep = s;
	active = false;
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;
	if (model == nullptr) return listParticles;
	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		newPos.x += distribution(gen) * sep;
		newPos.y += distribution(gen) * sep;
		newPos.z += distribution(gen) * sep;


		Vector3 newVel = meanVel;
		float ac = model->getAcceleration().y;
		if (move) {
			newVel.x += distribution(gen) * 10;
			newVel.y += distribution(gen) * .5;
			newVel.z += distribution(gen) * 10;

			ac += distribution(gen) * 20;
		}
		if (!move) newParticleType();
		Particle* newP = new Particle(model->getParticleType(), true);
		newP->setVelocity(newVel);
		newP->setPosition(newPos);
		if (move)
			newP->setAcceleration({ 0,-ac,0 });
		else newP->setAcceleration({ 0,0,0 });

		listParticles.push_back(newP);
	}
	return listParticles;
}

void UniformParticleGenerator::newParticleType()
{
	int t = rand() % 4 + 1;
	if (model != nullptr) {
		delete model;
		model = nullptr;
	}
	switch (t)
	{
	case 1:
		this->setParticle(new Particle(Artillery(meanVel, meanPos, 5000), false));
		break;
	case 2:
		this->setParticle(new Particle(Pistol(meanVel, meanPos, 5000), false));
		break;
	case 3:
		this->setParticle(new Particle(Laser(meanVel, meanPos, 5000), false));
		break;
	case 4:
		this->setParticle(new Particle(Fireball(meanVel, meanPos, 5000), false));
		break;
	case 5:
		this->setParticle(new Particle(GravityParticle1(meanPos, 5000), false));
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel, bool l, int nP)
{
	meanPos = _meanPos;
	meanVel = _meanVel;
	numParticles = nP;
	active = false;
	lluvia = l;
}

GaussianParticleGenerator::~GaussianParticleGenerator()
{
	if (model2 != nullptr)
		delete model2;
	if (model3 != nullptr)
		delete model3;
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (model == nullptr) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		newPos.x += dist(gen) * 200;
		newPos.y += dist(gen) * 100;
		newPos.z += dist(gen) * 200;

		Vector3 newVel = meanVel;
		newVel.x += dist(gen) * .1;
		newVel.y += dist(gen) * .1;
		newVel.z += dist(gen) * .1;
		Particle* newP = nullptr;
		if (lluvia) {
			int l = (rand() % 3);
			switch (l)
			{
			case 0:
				newP = new Particle(model->getParticleType(), true);
				break;
			case 1:
				newP = new Particle(model2->getParticleType(), true);
				break;
			case 2:
				newP = new Particle(model3->getParticleType(), true);
				break;
			default:
				break;
			}
		}
		else
			newP = new Particle(model->getParticleType(), true);
		newP->setPosition(newPos);
		newP->setVelocity(newVel);

		listParticles.push_back(newP);
	}
	return listParticles;
}

ParticleGenerator::~ParticleGenerator()
{
	if (model != nullptr) {
		delete model;
		model = nullptr;
	}
}

//Fuegos artificiales
FireworkGenerator::FireworkGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	meanPos = _meanPos;
	meanVel = _meanVel;
	numParticles = 10;
	active = false;
}

list<Firework*> FireworkGenerator::generateFireworks(Firework* parent)
{
	std::list<Firework*> listParticles;
	float increase = 360.0 / parent->getNumHijos();

	Vector3 newPos = parent->getPos();
	Vector3 newVel = parent->getVel();
	switch (parent->type())
	{
	case heart:
		FuegosCorazon(newVel, increase, parent, listParticles);
		break;
	case random:
		RandomFirework(newVel, parent, newPos, listParticles);
		break;
	case circle:
		CircleFirework(newVel, increase, parent, newPos, listParticles);
		break;
	case batFuego:
		BatFirework(newVel, increase, parent, newPos, listParticles);
		break;
	default:
		break;
	}


	return listParticles;
}
//Tipos de fireworks
void FireworkGenerator::BatFirework(Vector3& newVel, float increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		int x = increase * i;
		CabezaBatFuegos(newVel, parent, listParticles);
		FinAlasBatFuegos(newVel, x, parent, listParticles);
		ParentesisBatFuegos(x, newVel, parent, listParticles);
		PicosAbajoBatFuegos(x, newVel, parent, listParticles);
	}
}

void FireworkGenerator::FuegosCorazon(Vector3& newVel, float increase, Firework* parent, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		//Heart formula
		newVel.x = (16 * pow(sin(increase * i), 3)) * 10;
		newVel.y = (13 * cos(increase * i) - 5 * cos(2 * increase * i) - 2 * cos(3 * increase * i) - cos(4 * increase * i)) * 10;
		newVel.z = 0;

		Firework* newP = new Firework(FireworkHeart(15, { 0.0 ,0.0, 150.0 }), 0, parent->type(), true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
	}
}

void FireworkGenerator::CircleFirework(Vector3& newVel, float increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		newVel.x = cos(increase * i) * 20;
		newVel.y = sin(increase * i) * 20;
		newVel.z = 1;
		float color = 360.0 - parent->getNumHijos();
		Firework* newP = new Firework(RandomFireworks(std::rand() % 20 + 14, { color,1.0f,0.5f }, parent->getSize().x / 2, { 0.0 ,0.0, 100.0 }), parent->getNumHijos() - 10, parent->type(), true);

		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		newP->setAcceleration({ 0,-0.05,0 });
		listParticles.push_back(newP);
	}
}

void FireworkGenerator::RandomFirework(Vector3& newVel, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		//Uniform distribution
		newVel.x += distribution(gen) * 5;
		newVel.y -= distribution(gen) * 5;
		newVel.z += distribution(gen) * 5;

		float color = 360.0 / parent->getNumHijos();
		Firework* newP = new Firework(RandomFireworks(std::rand() % 50 + 14, { color,1.0f,0.5f }, parent->getSize().x / 2, { 0.0 ,0.0, 100.0 }), parent->getNumHijos() - 5, parent->type(), true);

		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		newP->setAcceleration({ 0,-0.5,0 });
		listParticles.push_back(newP);
	}
}
//F�rmulas Batfuegos
void FireworkGenerator::CabezaBatFuegos(Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles)
{
	for (int j = 0; j < 10; j++)
	{
		newVel.x = (10 - j * .2) * 10;
		newVel.y = (15 + j) * 10;
		Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
		Firework* newP2 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP2->setPosition(parent->getPos());
		newP2->setVelocity({ -newVel.x,newVel.y,newVel.z });
		listParticles.push_back(newP2);

		newVel = { 0,0,0 };
		newVel.x = (-4 - j * .5) * 10;
		newVel.y = (20 + j * .4) * 10;
		Firework* newP3 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP3->setPosition(parent->getPos());
		newP3->setVelocity(newVel);
		listParticles.push_back(newP3);
		Firework* newP4 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP4->setPosition(parent->getPos());
		newP4->setVelocity({ -newVel.x,newVel.y,newVel.z });
		listParticles.push_back(newP4);
	}
	for (int k = 0; k < 7; k++)
	{
		newVel.x = (-3 + k) * 10;
		newVel.y = 20 * 10;
		Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
	}
}

void FireworkGenerator::FinAlasBatFuegos(Vector3& newVel, int x, Firework* parent, std::list<Firework*>& listParticles)
{
	newVel = { 0,0,0 };
	if (sin(x) < 0 && cos(x) < 0) {

		newVel.x = (-10 + (10 * cos(x))) * 10;
		newVel.y = (25 + (10 * sin(x))) * 10;
	}
	Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP->setPosition(parent->getPos());
	newP->setVelocity(newVel);
	listParticles.push_back(newP);
	Firework* newP2 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP2->setPosition(parent->getPos());
	newP2->setVelocity({ -newVel.x,newVel.y,newVel.z });
	listParticles.push_back(newP2);
}

void FireworkGenerator::ParentesisBatFuegos(int x, Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles)
{
	for (int l = 0; l < 30; l++)
	{
		if (cos(x) * 2 > 0) {
			newVel.x = (20 + 5 * cos(x) * 2) * 10;
		}
		else {
			newVel.x = (5 * cos(x) * 2 - 20) * 10;
		}
		newVel.y = (12 + 3 * sin(x) * 4) * 10;
		newVel.z = 0;

		Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
	}
}

void FireworkGenerator::PicosAbajoBatFuegos(int x, Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles)
{
	newVel = { 0,0,0 };
	if (sin(x) > 0) {

		newVel.x = (-5 + 5 * cos(x)) * 10;
		newVel.y = (5 * sin(x)) * 10;
	}
	Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP->setPosition(parent->getPos());
	newP->setVelocity(newVel);
	listParticles.push_back(newP);
	Firework* newP2 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP2->setPosition(parent->getPos());
	newP2->setVelocity({ -200 - newVel.x,newVel.y,newVel.z });
	listParticles.push_back(newP2);
	Firework* newP3 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP3->setPosition(parent->getPos());
	newP3->setVelocity({ 200 + newVel.x,newVel.y,newVel.z });
	listParticles.push_back(newP3);
	Firework* newP4 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP4->setPosition(parent->getPos());
	newP4->setVelocity({ -newVel.x,newVel.y,newVel.z });
	listParticles.push_back(newP4);
}
//----------------------------------------------------------------------
list<Particle*> FireworkGenerator::generateParticles()
{
	return list<Particle*>();
}

GaussianSolidsGenerator::GaussianSolidsGenerator(PxPhysics* gP, PxScene* gS, Vector3 _meanPos, Vector3 _meanVel) : GaussianParticleGenerator(_meanPos, _meanVel, 1)
{
	numParticles = 30;
	gPhysics = gP;
	gScene = gS;
	model = nullptr;
}

Solids* GaussianSolidsGenerator::addRigids()
{
	gen.seed(rd());
	Solids* rigids;
	hsv color = {};
	color.h = dist(gen) * 100;
	color.s = 0.87;
	color.v = 0.97;
	rgb col = hsv2rgb(color);
	Vector3 newPos = meanPos;
	newPos.x += dist(gen) * 100;
	newPos.y += dist(gen) * 100;
	newPos.z += dist(gen) * 100;

	Vector3 newVel = meanVel;
	newVel.x += dist(gen);
	newVel.y += dist(gen);
	newVel.z += dist(gen);

	PxReal sizeX, sizeY, sizeZ;
	sizeX = std::abs(dist(gen) * 20);
	sizeY = std::abs(dist(gen) * 20);
	sizeZ = std::abs(dist(gen) * 20);
	SolidType ty;
	ty.size = { sizeX,sizeY,sizeZ };
	ty.col = { col.r,col.g,col.b,1.0 };
	PxMaterial* mat;
	mat = gPhysics->createMaterial((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 101) / 100);
	PxRigidDynamic* newRigid = gPhysics->createRigidDynamic(PxTransform(newPos));
	rigids = new Solids(meanPos, meanVel,
		gPhysics->createShape(PxBoxGeometry(sizeX, sizeY, sizeZ), *mat), newRigid, ty);
	gScene->addActor(*newRigid);
	return rigids;
}

GaussianSolidsGenerator::~GaussianSolidsGenerator()
{
}

UniformSolidsGenerator::UniformSolidsGenerator(PxPhysics* gP, PxScene* gS, Vector3 _meanPos, Vector3 _meanVel, int n,
	SolidType t, int x, int y, int z) :UniformParticleGenerator(_meanPos, _meanVel, n, false, 0)
{
	meanPos = _meanPos;
	meanVel = _meanVel;
	gPhysics = gP;
	gScene = gS;
	numParticles = n;
	type = t;
	facX = x;
	facY = y;
	facZ = z;

}

Solids* UniformSolidsGenerator::addRigids()
{
	Vector3 newPos = meanPos;
	newPos.x += distribution(gen) * facX;
	newPos.y += distribution(gen) * facY;
	newPos.z += distribution(gen) * facZ;


	Vector3 newVel = meanVel;
	//float ac = model->getAcceleration().y;

	newVel.x += distribution(gen) * 10;
	newVel.y += distribution(gen) * .5;
	newVel.z += distribution(gen) * 10;

	//ac += distribution(gen) * 20;
	PxReal size = 0.3;
	Solids* rigids=nullptr;


	PxMaterial* mat;
	if (type.gst == generalSolidType::General)
		mat = gPhysics->createMaterial((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 101) / 100);
	else
		mat = gPhysics->createMaterial(0.5, 0.5, 1);
	PxRigidDynamic* newRigid = gPhysics->createRigidDynamic(PxTransform(newPos));
	switch (type.gst)
	{
	case generalSolidType::Man1:
		rigids = new Solids(meanPos, meanVel, gPhysics->createShape(PxSphereGeometry(type.size.x), *mat), newRigid, type);
		break;
	case generalSolidType::Man2:
		rigids = new Solids(meanPos, meanVel, gPhysics->createShape(PxSphereGeometry(type.size.x), *mat), newRigid, type);
		break;
	case generalSolidType::Man3:
		rigids = new Solids(meanPos, meanVel, gPhysics->createShape(PxCapsuleGeometry(type.size.x,type.size.x), *mat), newRigid, type);
		break;
	default:
		rigids = new Solids(meanPos, meanVel, gPhysics->createShape(PxSphereGeometry(type.size.x), *mat), newRigid, type);
		break;
	}
	gScene->addActor(*newRigid);
	return rigids;
}

void UniformSolidsGenerator::changeVel(bool inc)
{
	if (inc) {
		if (meanVel.magnitude() < 100) {
			cout << meanVel.x << " " << meanVel.y << " " << meanVel.z << "\n";
			meanVel.x++;
		}
	}
	else if (meanVel.x > 10)
		meanVel.x--;
}

void UniformSolidsGenerator::setVel(Vector3 dir)
{
	meanVel = dir * 30;
}

void UniformSolidsGenerator::changeDir(Vector3 dir)
{
	dir.normalize();
	meanVel = { meanVel.x * dir.x, meanVel.y * dir.y, meanVel.z * dir.z };
}

void UniformSolidsGenerator::changefactors(int x, int y, int z) {
	facX = x; facY = y; facZ = z;
}