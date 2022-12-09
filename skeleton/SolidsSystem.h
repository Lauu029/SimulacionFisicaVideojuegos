#pragma once
#include "ParticleGenerator.h"
#include "SolidsForceRegistry.h"
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
	int numParticles = 0;
	int maxParticles = 20;
	int timeSinceLastAdding;
	SolidsForceRegistry* sFR = nullptr;
	SolidsWindGenerator* wind = nullptr;
public:
	SolidsSystem(PxPhysics* gPhysics, PxScene* gScene);
	void initSystem();
	void update(double t);
	void addWind();
	void deleteWind();
	~SolidsSystem();
	GaussianSolidsGenerator* getGen() { return generator; };
};

