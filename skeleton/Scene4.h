#pragma once
#include "Scene.h"
class Scene4 :public Scene
{
public:
	Scene4() {};
	~Scene4() {};
	virtual void initScene() override;
	virtual void updateScene(double t) override;
	virtual void keyPressed(unsigned char key) override;
};

