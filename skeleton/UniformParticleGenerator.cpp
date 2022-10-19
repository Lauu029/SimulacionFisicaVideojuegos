#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "UniformParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 0.5;
	numParticles = 10;
	active = false;
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (!model) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{

		auto p = model;

		Vector3 newPos = meanPos;
		newPos.x += distribution(gen)*.1;
		newPos.y += distribution(gen);
		newPos.z += distribution(gen)*.1;

		Vector3 newVel = meanVel;
		newVel.x += distribution(gen);
		newVel.y += distribution(gen)*10;
		newVel.z += distribution(gen);

		Particle* newP = new Particle(newPos, newVel, p->getAcceleration(), p->getDamping(), 
			p->getParticleType(),p->getSize(),p->getColor());

		listParticles.push_back(newP);
	}
	return listParticles;
}
