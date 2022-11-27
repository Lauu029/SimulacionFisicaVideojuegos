#include "Scene1.h"

void Scene1::initScene()
{
	suelo = new Particle(Suelo(), true);
	pS = new ParticleSystem(typeParticleSystem::ForceGenerators);
}

void Scene1::updateScene(double t)
{
	for (int i = 0; i < sceneParticles.size(); i++)
	{
		if (sceneParticles[i]->getPos().y < 0)
			sceneParticles[i]->killParticle();
		if (sceneParticles[i]->particleDeath()) {
			delete sceneParticles[i];
			sceneParticles[i] = nullptr;
			sceneParticles.erase(sceneParticles.begin() + i);
		}
		else
			sceneParticles[i]->integrate(t);
	}
	pS->update(t);
}

void Scene1::keyPressed(unsigned char key)
{
	Vector3 pos = GetCamera()->getTransform().p;
	Particle* p;
	switch (tolower(key))
	{
	case 'z':
		p = new Particle(Pistol(GetCamera()->getDir(), pos, 100), true);
		sceneParticles.push_back(p);
		pS->addGravity(p);
		break;
	case 'x':
		p = new Particle(Artillery(GetCamera()->getDir(), pos, 100), true);
		sceneParticles.push_back(p);
		pS->addGravity(p);
		break;
	case 'c':
		p = new Particle(Fireball(GetCamera()->getDir(), pos, 100), true);
		sceneParticles.push_back(p);
		pS->changeWind({ 0, 1000.0, 0 });
		pS->addWind(p);
		pS->addGravity(p);
		break;
	case 'v':
		p = new Particle(Laser(GetCamera()->getDir(), pos, 100), true);
		sceneParticles.push_back(p);
		pS->addGravity(p);
		break;
	default:
		break;
	}
}
