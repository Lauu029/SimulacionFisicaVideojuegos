#include "ParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "UniformParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 1;
	numParticles = 10;
	active = false;
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (model == nullptr) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		newPos.x += distribution(gen);
		newPos.y += distribution(gen);
		newPos.z += distribution(gen);

		Vector3 newVel = meanVel;
		newVel.x += distribution(gen) * 2;
		newVel.y += distribution(gen);
		newVel.z += distribution(gen) * 2;

		float ac = model->getAcceleration().y;
		ac += distribution(gen) * .3;
		Particle* newP = new Particle(model->getParticleType());
		newP->setVelocity(newVel);
		newP->setPosition(newPos);
		newP->setAcceleration({ 0,ac,0 });

		listParticles.push_back(newP);
	}
	return listParticles;
}


GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "GaussianParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 1;
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

		Particle* newP = new Particle(model->getParticleType());
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

FireworkGenerator::FireworkGenerator(Vector3 _meanPos, Vector3 _meanVel)
{

	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 1;
	numParticles = 10;
	active = false;
}

list<Firework*> FireworkGenerator::generateFireworks(Firework* parent)
{
	std::list<Firework*> listParticles;
	double increase = 360.0 / parent->getNumHijos();
	for (size_t i = 0; i < parent->getNumHijos(); i++)
	{
		Vector3 newPos = parent->getPos();
		//newPos.x += distribution(gen);
		//newPos.y += distribution(gen);
		//newPos.z += distribution(gen);

		Vector3 newVel = meanVel;
		newVel.x += cos(increase*i)*10;
		newVel.y +=-1 * abs((distribution(gen)));
		newVel.z += sin(increase*i)*10 ;
		/*Vector3 newVel=parent->getVel();
		newVel.x += 20 * dist(gen);
		newVel.y +=10 *dist(gen);
		newVel.z += 20 *dist(gen);*/
		Firework* newP = new Firework(Firework2(30), parent->getNumHijos() / 2);

		newP->setPosition(newPos);
		newP->setVelocity(newVel);
		newP->setAcceleration({ 0,-1,0 });
		//newP->setAcceleration({ 0,-2,0 });
		listParticles.push_back(newP);
		//FuegosCorazon(newVel, increase, i, parent, listParticles);
	}
	return listParticles;
}

void FireworkGenerator::FuegosCorazon(Vector3& newVel, double increase, const size_t& i, Firework* parent, std::list<Firework*>& listParticles)
{

	newVel.x = (16 * pow(sin(increase * i), 3));
	newVel.y = (13 * cos(increase * i) - 5 * cos(2 * increase * i) - 2 * cos(3 * increase * i) - cos(4 * increase * i));
	newVel.z = 0;

	Firework* newP = new Firework(Firework2(15), 0);
	newP->setPosition(parent->getPos());
	newP->setVelocity(newVel);
	//newP->setAcceleration({ 0,-2,0 });
	listParticles.push_back(newP);
}

list<Particle*> FireworkGenerator::generateParticles()
{
	return list<Particle*>();
}
