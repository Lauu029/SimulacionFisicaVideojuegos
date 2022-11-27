#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(typeParticleSystem pt)
{
	_typeSystem = pt;
	fg = new ForceRegistry();
	switch (pt)
	{
	case particleGenerators:
		fuente = new UniformParticleGenerator({ 0,0,100 }, { 0,30,0 }, 10, true, 1);
		fuente->setParticle(new Particle(Agua(), false));

		niebla = new GaussianParticleGenerator({ 10,50,150 }, { 0,0,0 });
		niebla->setParticle(new Particle(Nube(), false));

		fireworks = new FireworkGenerator({ 0,20,0 }, { 0,100,0 });
		fireworks->setParticle(new Firework(PresetFirework(200), 0, FireworkType::random, false));
		break;
	case ForceGenerators:
		gravity = new GravityGenerator({ 0,-9.8,0 });
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
		drag = new ParticleDragGenerator(0.01, 0.01);
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
		if (particles[i]->particleDeath()) {
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
			if (f[i]->getPos().y < 0)f[i]->killParticle();
			if (f[i]->particleDeath()) {
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
void ParticleSystem::addGravity(Particle* p)
{
	if (gravity == nullptr) gravity = new GravityGenerator({ 0,-9.8,0 });
	//si le pasan una partícula solo añade fuerza a esa partícula, si no se la añade a todas las partículas del sistema
	if (p != nullptr)
		fg->addRegistry(p, gravity);
	else {
		for (auto p : particles)
		{
			fg->addRegistry(p, gravity);
		}
	}
}
void ParticleSystem::deleteGravity()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(gravity);
	}
	delete gravity;
	gravity = nullptr;
}
void ParticleSystem::addWind(Particle* p)
{
	if (wind == nullptr) wind = new WindGenerator(30, { -50,20,0 }, { 70,50,5 });
	//si le pasan una partícula solo añade fuerza a esa partícula, si no se la añade a todas las partículas del sistema
	if (p != nullptr)
		fg->addRegistry(p, wind);
	else {
		for (auto p : particles)
		{
			fg->addRegistry(p, wind);
		}
	}
}
void ParticleSystem::deleteWind()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(wind);
	}
	delete wind;
	wind = nullptr;
}
void ParticleSystem::addTorbellino()
{
	if (torbellino == nullptr) torbellino = new TorbellinoGenerator(50, { 10,10,10 }, { -70,40,10 });
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
	delete torbellino;
	torbellino = nullptr;
}
void ParticleSystem::addExplosion()
{
	if(explosion==nullptr) explosion = new ExplosionGenerator(50, { 0,70,50 });
	for (Particle* p : particles)
	{
		fg->addRegistry(p, explosion);
	}
}
void ParticleSystem::deleteExplosion()
{
	for (Particle* p : particles)
	{
		fg->deleteForce(explosion);
	}
	delete explosion;
	explosion = nullptr;
}
void ParticleSystem::generateSpringDemo()
{
	//unión de dos partículas
	MuellesUnidos();
	//Goma
	GomaElastica();
	//Slinky
	addSlinky();
	//Partícula que flota
	FlotationSim();
	//Punto fijo
	MuelleFijo();
}
void ParticleSystem::MuelleFijo()
{
	Particle* p3 = new Particle(MuelleParticula({ 70.0,90.0,0.0 }), true);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 70.0,100.0,0.0 });
	fg->addRegistry(p3, f3);
	fg->addRegistry(p3, gravity);
	fg->addRegistry(p3, drag);

	springGenerators.push_back(f3);
	particles.push_back(p3);
}
void ParticleSystem::MuellesUnidos()
{
	Particle* p1 = new Particle(MuelleParticula({ 40.0,10.0,0.0 }), true);
	Particle* p2 = new Particle(MuelleParticula1({ 60.0,-10.0,0.0 }), true);
	p2->setMass(2.0);
	SpringForceGenerator* f1 = new SpringForceGenerator(5, 50, p2);
	fg->addRegistry(p1, f1);
	SpringForceGenerator* f2 = new SpringForceGenerator(5, 50, p1);
	fg->addRegistry(p2, f2);
	fg->addRegistry(p1, drag);
	fg->addRegistry(p2, drag);
	springGenerators.push_back(f1);
	springGenerators.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);
}
void ParticleSystem::GomaElastica()
{
	Particle* p1 = new Particle(MuelleParticula({ 0.0,70.0,0.0 }), true);
	Particle* p2 = new Particle(MuelleParticula1({ 20.0, 70.0,0.0 }), true);
	p2->setMass(2.0);
	GomaElasticaGenerator* f1 = new GomaElasticaGenerator(5, 20, p2);
	fg->addRegistry(p1, f1);
	GomaElasticaGenerator* f2 = new GomaElasticaGenerator(5, 20, p1);
	fg->addRegistry(p2, f2);
	fg->addRegistry(p1, gravity);
	fg->addRegistry(p1, drag);
	fg->addRegistry(p2, drag);
	springGenerators.push_back(f1);
	springGenerators.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);
}
void ParticleSystem::addSlinky()
{
	Vector3 pos = { -30.0,150.0,0.0 }, resta = { 0.0,5.0,0.0 };
	hsv col = { 10.0,0.7,0.7 };
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
		}
		else {
			fg->addRegistry(p1, gravity);

		}
		fg->addRegistry(p1, drag);

		particles.push_back(p1);
		slinky.push_back(p1);
		col.h += inc;
		colorRGB = hsv2rgb(col);
		colorAplica = { colorRGB.r, colorRGB.g, colorRGB.b,1.0 };
	}
	for (int i = 0; i < 9; i++)
	{
		SpringForceGenerator* sf = new SpringForceGenerator(20.0, 10.0, slinky[i + 1]);
		fg->addRegistry(slinky[i], sf);
		SpringForceGenerator* sf2 = new SpringForceGenerator(20.0, 10.0, slinky[i]);
		fg->addRegistry(slinky[i + 1], sf2);
		springGenerators.push_back(sf);
		springGenerators.push_back(sf2);
	}
}
void ParticleSystem::FlotationSim()
{
	bG = new BuoyancyForceGenerator(1.5, 0.0, 0.25, 100, { -100.0, 0.0, 0.0 });
	Particle* p = new Particle(Barquito({ -100.0,0.0,0.0 }), true);
	fg->addRegistry(p, bG);
	fg->addRegistry(p, gravity);
	fg->addRegistry(p, drag);
	particles.push_back(p);
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
	if (bG != nullptr)
		delete bG;
	if (drag != nullptr)
		delete drag;
	for (auto s : springGenerators)
		delete s;
	springGenerators.clear();
}
