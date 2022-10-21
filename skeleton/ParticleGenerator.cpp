#include "ParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "UniformParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 1;
	numParticles = 5;
	active = false;
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (model == nullptr) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		//newPos.x += distribution(gen);
		//newPos.y += distribution(gen);
		//newPos.z += distribution(gen) ;

		Vector3 newVel = meanVel;
		newVel.x += distribution(gen);
		newVel.y += distribution(gen);
		newVel.z += distribution(gen);

		float ac = model->getAcceleration().y;
		ac += distribution(gen) * .3;
		Particle* newP = new Particle(newPos, newVel, { 0,ac,0 }, model->getDamping(),
			model->getParticleType(), model->getSize(), model->getColor(), model->getRemainingTime());

		listParticles.push_back(newP);
	}
	return listParticles;
}


GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "UniformParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 1;
	numParticles = 5;
	active = false;
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (!model) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		auto p = model;

		Vector3 newPos = meanPos;
		newPos.x += dist(ran);
		newPos.y += dist(ran);
		newPos.z += dist(ran);

		Vector3 newVel = meanVel;
		newVel.x += dist(ran);
		newVel.y += dist(ran);
		newVel.z += dist(ran);

		float ac = p->getAcceleration().y;
		ac += dist(ran) * .3;
		Particle* newP = new Particle(newPos, newVel, { 0,ac,0 }, p->getDamping(),
			p->getParticleType(), p->getSize(), p->getColor(), p->getRemainingTime());

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
