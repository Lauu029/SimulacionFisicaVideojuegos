#include "Solids.h"

Solids::Solids(Vector3 _meanPos, Vector3 _meanVel, Vector4 col, PxReal s,
	PxShape* _gShape, PxRigidDynamic* rig)
{
	pos = _meanPos;
	vel = _meanVel;
	size = s;
	rigid = rig;
	rigid->setLinearVelocity((vel));
	rigid->setAngularVelocity(PxVec3(0, 0, 0));
	gShape = _gShape;
	rigid->attachShape(*gShape);
	item = new RenderItem(gShape, rigid, col);
}

Solids::~Solids()
{
	item->release();
}