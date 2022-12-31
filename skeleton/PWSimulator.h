#pragma once
#include "Scene.h"


class PWSimulator : public Scene
{
public:
	PWSimulator(PxPhysics* gPhysics, PxScene* gScene);
	~PWSimulator() override;
	virtual void initScene() override;
	virtual void updateScene(double t) override;
	virtual void keyPressed(unsigned char key) override;
	void changeLevel();
	int contadorFuegos;
protected:
	SolidsSystem* system = nullptr;
	int level;
};

