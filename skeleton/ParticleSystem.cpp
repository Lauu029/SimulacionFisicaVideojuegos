#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,10,0 });

	fuente->setParticle(new Particle(Agua()));

	niebla = new GaussianParticleGenerator({ 10,50,10 }, { 0,0,0 });
	niebla->setParticle(new Particle(Nube()));
}

void ParticleSystem::update(double t)
{

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->getPos().y < 0 || particles[i]->getRemainingTime() <= 0) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
			particles[i]->integrate(t);

	}
	for (int i = 0; i < fireworks.size(); i++)
	{
		if (fireworks[i]->getRemainingTime() <= 0) {
			list<Firework*> newFireworks = fireworks[i]->explode();
			delete fireworks[i];
			fireworks.erase(fireworks.begin() + i);
			for (auto f : newFireworks)
				fireworks.push_back(f);
			newFireworks.clear();
		}
		else
			fireworks[i]->integrate(t);

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

void ParticleSystem::generateFireworkSystem(particleType p)
{
	fireworks.push_back(new Firework(p, 10));
}

ParticleSystem::~ParticleSystem()
{
	for (auto p : particles)
	{
		delete p;
		p = nullptr;
	}
	particles.clear();
	for (auto f : fireworks) {
		delete f;
		f = nullptr;
	}
	fireworks.clear();
	delete niebla;
	niebla = nullptr;
	delete fuente;
	fuente = nullptr;
}
