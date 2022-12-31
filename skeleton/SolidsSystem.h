#pragma once
#include "ParticleGenerator.h"
#include "SolidsForceRegistry.h"
#include "MyPxSimulationEventCallback.h"
enum typeSolidSystem { PowerWash, NormalSolids };
class SolidsSystem
{
protected:
	vector<Solids*>solidParticles;
	Solids* mainCharacter = nullptr;
	GaussianSolidsGenerator* generator = nullptr;
	UniformSolidsGenerator* manguera1 = nullptr;
	UniformSolidsGenerator* manguera2 = nullptr;
	UniformSolidsGenerator* manguera3 = nullptr;
	UniformSolidsGenerator* Suciedades = nullptr;
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
	Camera* cam = nullptr;
	vector<Solids*> dirt;
	MyPxSimulationEventCallback* callback = nullptr;
	int level;
public:
	SolidsSystem(PxPhysics* gPhysics, PxScene* gScene, typeSolidSystem type, int l=0);
	void initSystem();
	void CreateNormalSystem();
	void createPWSystem();
	void createLevel1();
	void update(double t);
	void addWind();
	void changeWaterVel(bool inc);
	void deleteWind();
	void moveCharacter(Vector3 dir);
	void keyPressed(unsigned char key);
	void changeFontActive(int numFuente, bool act);
	void putDirt(Vector3 const& posMuro, Vector3 const& sizeMuro, SolidType tipeDirt, int minAmount);
	int getDirtAmount() { return dirt.size(); };
	
	~SolidsSystem();
	GaussianSolidsGenerator* getGen() { return generator; };
};

