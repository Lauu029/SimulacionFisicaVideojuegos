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
		newVel.x += distribution(gen)*2;
		newVel.y += distribution(gen);
		newVel.z += distribution(gen)*2;

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
	numParticles =200;
	active = false;
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (model==nullptr) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		Vector3 newPos = meanPos;
		newPos.x += dist(ran)*10;
		newPos.y += dist(ran)*5;
		newPos.z += dist(ran)*10;

		Vector3 newVel = meanVel;
		newVel.x += dist(ran)*.1;
		newVel.y += dist(ran)*.1;
		newVel.z += dist(ran)*.1;

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
