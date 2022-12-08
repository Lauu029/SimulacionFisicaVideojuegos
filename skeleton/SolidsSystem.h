#pragma once
#include "ParticleGenerator.h"
class SolidsSystem
{
protected:
	vector<Solids*>solidParticles;
	GaussianSolidsGenerator* generator = nullptr;
	RenderItem* item = nullptr;
	RenderItem* itemWall = nullptr;
	PxRigidStatic* floor = nullptr;
	PxRigidStatic* wall = nullptr;
	PxScene* sC = nullptr;
	PxPhysics* sP = nullptr;
	int numParticles=0;
	int maxParticles=7;
public:
	SolidsSystem(PxPhysics* gPhysics, PxScene* gScene);
	void initSystem();
	void update(double t);
	~SolidsSystem();
	GaussianSolidsGenerator* getGen() { return generator; };
};

