#pragma once
#include "Scene.h"
class Scene2 : public Scene
{
public:
	Scene2(PxPhysics* gPhysics, PxScene* gScene) :Scene(gPhysics,gScene) {};
	~Scene2() {};
	virtual void initScene() override;
	virtual void updateScene(double t) override;
	virtual void keyPressed(unsigned char key) override;
};

