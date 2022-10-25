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
		Vector3 newVel = parent->getVel();
		switch (parent->type())
		{
		case heart:
			FuegosCorazon(newVel, increase, i, parent, listParticles);
			break;
		case random:
			RandomFirework(newVel, parent, newPos, listParticles);
			break;
		case circle:
			CircleFirework(newVel, increase, i, parent, newPos, listParticles);
			break;
		default:
			break;
		}

	}
	return listParticles;
}

void FireworkGenerator::CircleFirework(Vector3& newVel, double increase, const size_t& i, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{
	newVel.x = sqrt(pow(cos(increase * i), 2) / 2) * pow(-1, i) ;
	newVel.y = sin(increase * i);
	newVel.z = -sqrt(pow(cos(increase * i), 2) / 2) * pow(-1,  i) ;
	float color = 250.0 / parent->getNumHijos();
	Firework* newP = new Firework(RandomFireworks(std::rand() % 20 + 14, { color,1.0f,0.5f }), parent->getNumHijos() -10, parent->type());

	newP->setPosition(newPos);
	newP->setVelocity(newVel);
	newP->setAcceleration({ 0,-0.05,0 });
	listParticles.push_back(newP);

}

void FireworkGenerator::RandomFirework(Vector3& newVel, Firework* parent, Vector3& newPos, std::list<Firework*>& listParticles)
{

	newVel.x += distribution(gen);
	newVel.y += distribution(gen);
	newVel.z += distribution(gen);
	float color = 360.0 / parent->getNumHijos();
	Firework* newP = new Firework(RandomFireworks(std::rand() % 14 + 14, { color,1.0f,0.5f }), parent->getNumHijos() / 2, parent->type());

	newP->setPosition(newPos);
	newP->setVelocity(newVel);
	newP->setAcceleration({ 0,-0.05,0 });
	listParticles.push_back(newP);
}

void FireworkGenerator::FuegosCorazon(Vector3& newVel, double increase, const size_t& i, Firework* parent, std::list<Firework*>& listParticles)
{

	newVel.x = (16 * pow(sin(increase * i), 3)) / 2;
	newVel.y = (13 * cos(increase * i) - 5 * cos(2 * increase * i) - 2 * cos(3 * increase * i) - cos(4 * increase * i)) / 2;
	newVel.z = 0;
	Firework* newP = new Firework(FireworkHeart(FireworkHeart(15)), 0, parent->type());
	newP->setPosition(parent->getPos());
	newP->setVelocity(newVel);
	//newP->setAcceleration({ 0,-2,0 });
	listParticles.push_back(newP);
}

list<Particle*> FireworkGenerator::generateParticles()
{
	return list<Particle*>();
}
