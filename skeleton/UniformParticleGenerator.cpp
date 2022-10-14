#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 _meanPos, Vector3 _meanVel)
{
	name = "UniformParticles";
	meanPos = _meanPos;
	meanVel = _meanVel;
	generationProb = 0.5;
	numParticles = 5;


	model = new Particle({ 0,0,0 }, { 0.1, 0.1, 0.1 }, { 0,-.5,0 }, 0.9);
	model->setRender(particleType::Sphere, 0.4, { 0.94, 0.97,1,0.6 });



}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> listParticles;

	if (!model) return listParticles;

	for (size_t i = 0; i < numParticles; i++)
	{
		if (distribution(gen) <= generationProb) {
			auto p = model;

			Vector3 newPos = meanPos;
			newPos.x += distribution(gen);
			newPos.y += distribution(gen);
			newPos.z += distribution(gen);

			Vector3 newVel = meanVel;
			newVel.x += distribution(gen);
			newVel.y += distribution(gen);
			newVel.z += distribution(gen);

			Particle* newP = new Particle(newPos, newVel, p->getAcceleration(), p->getDamping());

			listParticles.push_back(newP);
		}
	}
	return listParticles;
}
