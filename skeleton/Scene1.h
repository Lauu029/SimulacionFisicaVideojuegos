#pragma once
#include "Scene.h"
//Disparo de partículas
class Scene1 : public Scene
{
public:
	Scene1(PxPhysics* gPhysics, PxScene* gScene):Scene(gPhysics,gScene) {};
	~Scene1() {};
	virtual void initScene()override;
	virtual void updateScene(double t) override;
	virtual void keyPressed(unsigned char key)override;
};

