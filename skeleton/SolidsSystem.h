#pragma once
#include "ParticleGenerator.h"
#include "SolidsForceRegistry.h"
enum typeSolidSystem { PowerWash, NormalSolids };
class SolidsSystem
{
protected:
	vector<Solids*>solidParticles;
	Solids* mainCharacter = nullptr;
	GaussianSolidsGenerator* generator = nullptr;
	UniformSolidsGenerator* manguera = nullptr;
	RenderItem* item = nullptr;
	RenderItem* itemWall = nullptr;
	PxRigidStatic* floor = nullptr;
	PxRigidStatic* wall = nullptr;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	int numParticles = 0;
	int maxParticles = 20;
	int timeSinceLastAdding;
	SolidsForceRegistry* sFR = nullptr;
	SolidsWindGenerator* wind = nullptr;
	typeSolidSystem t;
public:
	SolidsSystem(PxPhysics* gPhysics, PxScene* gScene, typeSolidSystem type);
	void initSystem();
	void CreateNormalSystem();
	void createPWSystem();
	void update(double t);
	void addWind();
	void deleteWind();
	void moveCharacter(Vector3 dir);
	~SolidsSystem();
	GaussianSolidsGenerator* getGen() { return generator; };
};

