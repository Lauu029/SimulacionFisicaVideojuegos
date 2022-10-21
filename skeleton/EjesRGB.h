#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"


using namespace physx;


class EjesRGB {
public:
	EjesRGB(int x);
	~EjesRGB();
private:
	RenderItem* ejeX,* ejeY,* ejeZ;
	PxTransform trX, trY, trZ;
};

EjesRGB::EjesRGB(int x) {
	trX = PxTransform({ 0,0,0 });
	trY = PxTransform({ 0,0,0 });
	trZ = PxTransform({ 0,0,0 });

	ejeX = new RenderItem(CreateShape(PxBoxGeometry(x, 0.5, 0.5)), &trX, { 1, 0, 0, 1 });
	ejeY = new RenderItem(CreateShape(PxBoxGeometry(0.5, x, 0.5)), &trY, { 0, 1, 0, 1 });
	ejeZ = new RenderItem(CreateShape(PxBoxGeometry(0.5, 0.5, x)), &trZ, { 0, 0, 1, 1 });
}

EjesRGB::~EjesRGB() {
	DeregisterRenderItem(ejeX); delete ejeX;
	DeregisterRenderItem(ejeY); delete ejeY;
	DeregisterRenderItem(ejeZ); delete ejeZ;
}