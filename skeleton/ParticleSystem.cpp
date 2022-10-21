#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,5,0 });
	fuente->setParticle(new Particle({ 0,0,0 }, { 0.1, 0.1, 0.1 }, { 0,-.5,0 }, 0.9,
		particleType::Sphere, { 0.5, 0, 0 }, { 0, 0.97,1,.9 }, 60));

	niebla = new GaussianParticleGenerator({ 20,10,10 }, { 0,0,0 });
	niebla->setParticle(new Particle({ 1,1,1 }, { 0,0,0 }, { 0,0,0 }, 0.8,
		particleType::Sphere, { 0.2,0,0 }, { 1,1,.3,1 }, 20));
}

void ParticleSystem::update(double t)
{

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->getPos().y < 0 || particles[i]->getRemainingTime() < 0) {
			delete particles[i];
			particles[i] = nullptr;
			particles.erase(particles.begin() + i);
		}
		else
			particles[i]->integrate(t);

	}
	
	if (fuente != nullptr && fuente->isActive()) {

		list<Particle*> newParticles = fuente->generateParticles();
		for (auto a : newParticles)
			particles.push_back(a);
		newParticles.clear();
	}
	if (niebla != nullptr && niebla->isActive()) {
		list<Particle*> newParticles = niebla->generateParticles();
		for (auto a : newParticles)
			particles.push_back(a);
		newParticles.clear();
	}

}

ParticleGenerator* ParticleSystem::getParticleGenerator(typeParticleSystem t)
{
	switch (t)
	{
	case font:
		return fuente;
		break;
	case fog:
		return niebla;
		break;
	default:
		break;
	}
}

ParticleSystem::~ParticleSystem()
{
	for (auto p : particles)
	{
		delete p;
		p = nullptr;
	}
	particles.clear();
	delete niebla;
	niebla = nullptr;
	delete fuente;
	fuente = nullptr;
}
