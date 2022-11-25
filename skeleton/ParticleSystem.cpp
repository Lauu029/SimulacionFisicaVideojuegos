#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(typeParticleSystem pt)
{
	_typeSystem = pt;
	fg = new ForceRegistry();
	switch (pt)
	{
	case particleGenerators:
		fuente = new UniformParticleGenerator({ 0,0,0 }, { 0,10,0 }, 10, true, 1);
		fuente->setParticle(new Particle(Agua(), false));

		niebla = new GaussianParticleGenerator({ 10,50,10 }, { 0,0,0 });
		niebla->setParticle(new Particle(Nube(), false));

		fireworks = new FireworkGenerator({ 0,20,0 }, { 0,10,0 });
		fireworks->setParticle(new Firework(PresetFirework(20), 0, FireworkType::random, false));
		break;
	case ForceGenerators:
		gravity = new GravityGenerator({ 0,-29.8,0 });
		GravityParticles = new UniformParticleGenerator({ 0,60,0 }, { 0,0,0 }, 100, false, 70);
		GravityParticles->setParticle(new Particle(GravityParticle1({ 0,0,0 }, 0), false));

		wind = new WindGenerator(30, { -50,20,0 }, { 70,50,5 });
		WindParticles = new UniformParticleGenerator({ 70,50,0 }, { 0,0,0 }, 500, false, 20);
		WindParticles->setParticle(new Particle(GravityParticle1({ 0,0,0 }, 0), false));

		torbellino = new TorbellinoGenerator(50, { 10,10,10 }, { -70,40,10 });
		TorbellinoParticles = new UniformParticleGenerator({ -70,40,0 }, { 0,0,0 }, 500, false, 30);
		TorbellinoParticles->setParticle(new Particle(GravityParticle1({ 0,0,0 }, 0), false));

		explosion = new ExplosionGenerator(50, { 0,70,50 });
		ExplosionParticles = new UniformParticleGenerator({ 0,70,50 }, { 0,0,0 }, 700, false, 40);
		ExplosionParticles->setParticle(new Particle(GravityParticle1({ 0,0,0 }, 0), false));
		break;
	case SpringsGenerators:
		gravity = new GravityGenerator({ 0,-9.8,0 });
		generateSpringDemo();
		break;
	default:
		break;
	}
}
void ParticleSystem::GenerateForceParticles(typeForceSystem tf)
{
	list<Particle*> newParticles;
	switch (tf)
	{
	case type_explosion:
		newParticles = ExplosionParticles->generateParticles();
		break;
	case type_gravity:
		newParticles = GravityParticles->generateParticles();
		break;
	case type_wind:
		newParticles = WindParticles->generateParticles();
		break;
	case type_torbellino:
		newParticles = TorbellinoParticles->generateParticles();
		break;
	default:
		break;
	}
	for (auto a : newParticles)
		particles.push_back(a);
	newParticles.clear();
}
void ParticleSystem::update(double t)
{
	if (fg != nullptr)
		fg->updateForces(t);
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->getRemainingTime() <= 0) {
			if (fg != nullptr) fg->deleteParticle(particles[i]);
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
			particles[i]->integrate(t);
	}
	if (_typeSystem == typeParticleSystem::particleGenerators) {

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
}
void ParticleSystem::addGravity()
{
	for (Particle* p : particles)
	{
		fg->addRegistry(p, gravity);
	}
}
void ParticleSystem::deleteGravity()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(gravity);
	}
}
void ParticleSystem::addWind()
{
	for (Particle* p : particles)
	{
		fg->addRegistry(p, wind);
	}
}
void ParticleSystem::deleteWind()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(wind);
	}
}
void ParticleSystem::addTorbellino()
{
	for (Particle* p : particles)
	{
		fg->addRegistry(p, torbellino);
	}
}
void ParticleSystem::deleteTorbellino()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(torbellino);
	}
}
void ParticleSystem::addExplosion()
{
	for (Particle* p : particles)
	{
		fg->addRegistry(p, explosion);
	}
}
void ParticleSystem::generateSpringDemo()
{
	//unión de dos partículas
	MuellesUnidos();
	GomaElastica();
	addSlinky();
	//Punto fijo
	MuelleFijo();
}
void ParticleSystem::MuelleFijo()
{
	Particle* p3 = new Particle(MuelleParticula({ 70.0,50.0,0.0 }), true);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(5, 10, { 70.0,100.0,0.0 });
	fg->addRegistry(p3, f3);
	fg->addRegistry(p3, gravity);
	springGenerators.push_back(f3);
	particles.push_back(p3);
}
void ParticleSystem::MuellesUnidos()
{
	Particle* p1 = new Particle(MuelleParticula({ 40.0,10.0,0.0 }), true);
	Particle* p2 = new Particle(MuelleParticula1({ 70.0,-10.0,0.0 }), true);
	p2->setMass(2.0);
	SpringForceGenerator* f1 = new SpringForceGenerator(7, 20, p2);
	fg->addRegistry(p1, f1);
	SpringForceGenerator* f2 = new SpringForceGenerator(7, 20, p1);
	fg->addRegistry(p2, f2);
	springGenerators.push_back(f1);
	springGenerators.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);
}
void ParticleSystem::GomaElastica()
{
	Particle* p1 = new Particle(MuelleParticula({ 0.0,70.0,0.0 }), true);
	Particle* p2 = new Particle(MuelleParticula1({ 10.0, 70.0,0.0 }), true);
	p2->setMass(2.0);
	GomaElasticaGenerator* f1 = new GomaElasticaGenerator(5, 10, p2);
	fg->addRegistry(p1, f1);
	GomaElasticaGenerator* f2 = new GomaElasticaGenerator(5, 10, p1);
	fg->addRegistry(p2, f2);
	fg->addRegistry(p1, gravity);
	springGenerators.push_back(f1);
	springGenerators.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);
}
void ParticleSystem::addSlinky()
{
	Vector3 pos = { -30.0,150.0,0.0 }, resta = { 0.0,5.0,0.0 };
	hsv col = { 100.0,0.7,0.7 };
	float inc = 20.0;
	rgb colorRGB = hsv2rgb(col);
	Vector4 colorAplica = { colorRGB.r, colorRGB.g, colorRGB.b,1.0 };
	vector<Particle*> slinky;
	for (int i = 0; i < 10; i++)
	{
		pos = pos - resta;
		Particle* p1 = new Particle(MuelleParticula(pos), true);
		p1->setColor(colorAplica);
		if (!i) {
			p1->setMass(0.0);
			p1->setDampling(0.0);
		}
		else
			fg->addRegistry(p1, gravity);

		particles.push_back(p1);
		slinky.push_back(p1);
		col.h += inc;
		colorRGB = hsv2rgb(col);
		colorAplica = { colorRGB.r, colorRGB.g, colorRGB.b,1.0 };
	}
	for (int i = 0; i < 9; i++)
	{
		SpringForceGenerator* sf = new SpringForceGenerator(30.0,5.0,slinky[i+1]);
		fg->addRegistry(slinky[i], sf);
		SpringForceGenerator* sf2 = new SpringForceGenerator(30.0,5.0, slinky[i]);
		fg->addRegistry(slinky[i + 1], sf2);
		springGenerators.push_back(sf);
		springGenerators.push_back(sf2);
	}
}
ParticleGenerator* ParticleSystem::getParticleGenerator(typeParticleGenerator t)
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
		f.push_back(new Firework(PresetFirework(10), 50, t, true));
		break;
	case random:
		f.push_back(new Firework(PresetFirework(10), 10, t, true));
		break;
	case circle:
		f.push_back(new Firework(PresetFirework(10), 20, t, true));
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
		delete p;
	particles.clear();

	for (auto fi : f)
		delete fi;
	f.clear();

	if (GravityParticles != nullptr)
		delete GravityParticles;
	if (ExplosionParticles != nullptr)
		delete ExplosionParticles;
	if (TorbellinoParticles != nullptr)
		delete TorbellinoParticles;
	if (WindParticles != nullptr)
		delete WindParticles;
	if (fireworks != nullptr)
		delete fireworks;
	if (niebla != nullptr)
		delete niebla;
	if (fuente != nullptr)
		delete fuente;
	if (fg != nullptr)
		delete fg;
	if (gravity != nullptr)
		delete gravity;
	if (wind != nullptr)
		delete wind;
	if (torbellino != nullptr)
		delete torbellino;
	if (explosion != nullptr)
		delete explosion;
	for (auto s : springGenerators)
		delete s;
	springGenerators.clear();
}
