#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,10,0 });
	fuente->setParticle(new Particle(Agua(),false));

	niebla = new GaussianParticleGenerator({ 10,50,10 }, { 0,0,0 });
	niebla->setParticle(new Particle(Nube(),false));

	fireworks = new FireworkGenerator({ 0,20,0 }, { 0,10,0 });
	fireworks->setParticle(new Firework(PresetFirework(20), 0,FireworkType::random,false));
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
void ParticleSystem::generateFireworkSystem(FireworkType t)
{
	switch (t)
	{
	case heart:
		f.push_back(new Firework(PresetFirework(10), 50,t,true));
		break;
	case random:
		f.push_back(new Firework(PresetFirework(10), 10, t,true));
		break;
	case circle:
		f.push_back(new Firework(PresetFirework(10), 20, t,true));
		break;
	case batFuego:
		f.push_back(new Firework(BatFireworks(5), 50, t, true));
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
