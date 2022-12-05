#pragma once
#include "Scene.h"
class Scene3 : public Scene
{
public:
	Scene3(PxPhysics* gPhysics, PxScene* gScene) :Scene(gPhysics,gScene) {};
	~Scene3() {};
	virtual void initScene() override;
	virtual void updateScene(double t)override;
	virtual void keyPressed(unsigned char key) override;
};

