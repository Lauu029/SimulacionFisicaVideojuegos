#include "PWSimulator.h"

void PWSimulator::initScene()
{
	suelo = new Particle(Suelo(), true);
	hsv color = { 25.0,0.93,0.48 };
	rgb col = hsv2rgb(color);
	suelo->setColor({ col.r,col.g,col.b,1.0 });
}

void PWSimulator::updateScene(double t)
{
}

void PWSimulator::keyPressed(unsigned char key)
{
}
