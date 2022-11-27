#pragma once
#include "Scene.h"
class Scene3 : public Scene
{
public:
	Scene3() {};
	~Scene3() {};
	virtual void initScene() override;
	virtual void updateScene(double t)override;
	virtual void keyPressed(unsigned char key) override;
};

