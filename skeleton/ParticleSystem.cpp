#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	//fuente = nullptr;
	fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,10,0 });
	fuente->setParticle(new Particle({ 0,0,0 }, { 0.1, 0.1, 0.1 }, { 0,-.5,0 }, 0.9,
		particleType::Sphere, { 0.1, 0, 0 }, { 0, 0.97,1,.9 },60));

}

void ParticleSystem::update(double t)
{

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->getPos().y < 0 || particles[i]->getRemainingTime() < 0) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
			particles[i]->integrate(t);

	}
	/*for (auto pg : particleGenerators)
	{*/
	if (fuente != nullptr && fuente->isActive()) {

		list<Particle*> newParticles = fuente->generateParticles();
		for (auto a : newParticles)
			particles.push_back(a);
		newParticles.clear();
	}
	//}
}

void ParticleSystem::setParticleGenerators(typeParticleSystem type)
{
	switch (type)
	{
	case font:
		if (!fuente->isActive())
			for (int i = 0; i < particles.size(); i++)
			{
				delete particles[i];
				particles.erase(particles.begin() + i);
			}
		//fuente = nullptr;
		break;
	case fog:
		break;
	default:
		break;
	}

	//particleGenerators.push_back(fuente);

	//fuente
}

void ParticleSystem::activateParticleGenerators(typeParticleSystem type)
{
	switch (type)
	{
	case font:

		setParticleGenerators(typeParticleSystem::font);
		fuente->setActive();
		break;
	case fog:
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
	}
	particles.clear();
	for (auto pg : particleGenerators)
	{
		delete pg;

	}
	particleGenerators.clear();
	delete fuente;
	fuente = nullptr;
}
