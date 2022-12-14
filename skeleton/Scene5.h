#pragma once
#include "Scene.h"

class Scene5 : public Scene
{
public:
	Scene5(PxPhysics* gPhysics, PxScene* gScene);
	~Scene5() override;
	virtual void initScene() override;
	virtual void updateScene(double t) override;
	virtual void keyPressed(unsigned char key) override;
protected:
	SolidsSystem* system = nullptr;
};

