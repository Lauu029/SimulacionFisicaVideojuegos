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
protected:
	void clearLevel();
	void changeLevel();
	int contadorFuegos;
	SolidsSystem* system = nullptr;
	int level;
	bool shouldIChange = true;
};

