#include "ParticleGenerator.h"
//Generadores de partículas
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
			newVel.x += distribution(gen) * 2;
			newVel.y += distribution(gen);
			newVel.z += distribution(gen) * 2;

			ac += distribution(gen) * .3;
		}
		if (!move) newParticleType();
		Particle* newP = new Particle(model->getParticleType(), true);
		newP->setVelocity(newVel);
		newP->setPosition(newPos);
		if (move)
			newP->setAcceleration({ 0,ac,0 });
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
		this->setParticle(new Particle(Artillery(meanVel, meanPos, 500), false));
		break;
	case 2:
		this->setParticle(new Particle(Pistol(meanVel, meanPos, 500), false));
		break;
	case 3:
		this->setParticle(new Particle(Laser(meanVel, meanPos, 500), false));
		break;
	case 4:
		this->setParticle(new Particle(Fireball(meanVel, meanPos, 500), false));
		break;
	case 5:
		this->setParticle(new Particle(GravityParticle1(meanPos, 500), false));
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	meanPos = _meanPos;
	meanVel = _meanVel;
	numParticles = 200;
	active = false;
}
list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (model == nullptr) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		newPos.x += dist(gen) * 10;
		newPos.y += dist(gen) * 5;
		newPos.z += dist(gen) * 10;

		Vector3 newVel = meanVel;
		newVel.x += dist(gen) * .1;
		newVel.y += dist(gen) * .1;
		newVel.z += dist(gen) * .1;

		Particle* newP = new Particle(model->getParticleType(), true);
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
	double increase = 360.0 / parent->getNumHijos();

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
void FireworkGenerator::BatFirework(Vector3& newVel, double increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
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
void FireworkGenerator::FuegosCorazon(Vector3& newVel, double increase, Firework* parent, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		//Heart formula
		newVel.x = (16 * pow(sin(increase * i), 3)) / 2;
		newVel.y = (13 * cos(increase * i) - 5 * cos(2 * increase * i) - 2 * cos(3 * increase * i) - cos(4 * increase * i)) / 2;
		newVel.z = 0;

		Firework* newP = new Firework(FireworkHeart(15), 0, parent->type(), true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
	}
}
void FireworkGenerator::CircleFirework(Vector3& newVel, double increase, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{
	for (size_t i = 1; i <= parent->getNumHijos(); i++)
	{
		newVel.x = cos(increase * i);
		newVel.y = sin(increase * i);
		newVel.z = 1;
		/*newVel.x = sqrt(pow(cos(increase * i), 2) / 2) * pow(-1, i);
		newVel.y = sin(increase * i);
		newVel.z = -sqrt(pow(cos(increase * i), 2) / 2) * pow(-1, i);*/
		float color = 360.0 - parent->getNumHijos();
		Firework* newP = new Firework(RandomFireworks(std::rand() % 20 + 14, { color,1.0f,0.5f }, parent->getSize().x / 2), parent->getNumHijos() - 10, parent->type(), true);

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
		newVel.x += distribution(gen);
		newVel.y += distribution(gen);
		newVel.z += distribution(gen);

		float color = 360.0 / parent->getNumHijos();
		Firework* newP = new Firework(RandomFireworks(std::rand() % 14 + 14, { color,1.0f,0.5f }, parent->getSize().x / 2), parent->getNumHijos() / 2, parent->type(), true);

		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		newP->setAcceleration({ 0,-0.05,0 });
		listParticles.push_back(newP);
	}
}
//Fórmulas Batfuegos
void FireworkGenerator::CabezaBatFuegos(Vector3& newVel, Firework* parent, std::list<Firework*>& listParticles)
{
	for (int j = 0; j < 10; j++)
	{
		newVel.x = 10 - j * .2;
		newVel.y = 15 + j;
		Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP->setPosition(parent->getPos());
		newP->setVelocity(newVel);
		listParticles.push_back(newP);
		Firework* newP2 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
		newP2->setPosition(parent->getPos());
		newP2->setVelocity({ -newVel.x,newVel.y,newVel.z });
		listParticles.push_back(newP2);

		newVel = { 0,0,0 };
		newVel.x = -4 - j * .5;
		newVel.y = 20 + j * .4;
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
		newVel.x = -3 + k;
		newVel.y = 20;
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

		newVel.x = -10 + (10 * cos(x));
		newVel.y = 25 + (10 * sin(x));
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
			newVel.x = 20 + 5 * cos(x) * 2;
		}
		else {
			newVel.x = 5 * cos(x) * 2 - 20;
		}
		newVel.y = 12 + 3 * sin(x) * 4;
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

		newVel.x = -5 + 5 * cos(x);
		newVel.y = 5 * sin(x);
	}
	Firework* newP = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP->setPosition(parent->getPos());
	newP->setVelocity(newVel);
	listParticles.push_back(newP);
	Firework* newP2 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP2->setPosition(parent->getPos());
	newP2->setVelocity({ -20 - newVel.x,newVel.y,newVel.z });
	listParticles.push_back(newP2);
	Firework* newP3 = new Firework(parent->getParticleType(), 0, FireworkType::batFuego, true);
	newP3->setPosition(parent->getPos());
	newP3->setVelocity({ 20 + newVel.x,newVel.y,newVel.z });
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
