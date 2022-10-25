#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,10,0 });
	fuente->setParticle(new Particle(Agua()));

	niebla = new GaussianParticleGenerator({ 10,50,10 }, { 0,0,0 });
	niebla->setParticle(new Particle(Nube()));

	fireworks = new FireworkGenerator({ 0,20,0 }, { 0,10,0 });

	fireworks->setParticle(new Firework(Firework1(20), 20));
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
	for (int i = 0; i < f.size(); i++)
	{
		if (f[i]->getPos().y < 0 || f[i]->getRemainingTime() <= 0) {
			f[i]->explode();
		}
		else
			f[i]->integrate(t);
	}
	//if (fireworks != nullptr && fireworks->isActive()) {
		for (int i = 0; i < f.size(); i++)
		{
			if (!f[i]->isActive()) {
				list<Firework*> newParticles = fireworks->generateFireworks(f[i]);
				for (auto a : newParticles)
					f.push_back(a);
				newParticles.clear();
				delete f[i];
				f.erase(f.begin() + i);
			}
		}
	//}
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
	case firework:
		return fireworks;
		break;
	default:
		break;
	}
}

void ParticleSystem::generateFireworkSystem(particleType p)
{
	f.push_back(new Firework(p, 10));
}

ParticleSystem::~ParticleSystem()
{
	for (auto p : particles)
	{
		delete p;
		p = nullptr;
	}
	particles.clear();
	for (auto fi : f) {
		delete fi;
		fi = nullptr;
	}
	f.clear();
	delete fireworks;
	fireworks = nullptr;
	delete niebla;
	niebla = nullptr;
	delete fuente;
	fuente = nullptr;
}
