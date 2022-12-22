#include "Solids.h"

Solids::Solids(Vector3 _meanPos, Vector3 _meanVel, Vector4 col, Vector3 s,
	PxShape* _gShape, PxRigidDynamic* rig, bool render)
{
	pos = _meanPos;
	vel = _meanVel;
	rigid = rig;
	rigid->setLinearVelocity((vel));
	rigid->setAngularVelocity(PxVec3(0, 0, 0));
	gShape = _gShape;
	rigid->attachShape(*gShape);
	rigid->setMassSpaceInertiaTensor({ s.y * s.z, s.x * s.z, s.x * s.y });
	if (render)
	item = new RenderItem(gShape, rigid, col);
	time = 0;
	force = { 0, 0, 0 };
	
}
void Solids::update(double t) {
	time++;
	if (time > 100) kill();
	if (rigid->getGlobalPose().p.y < 0) kill();
	if (force.magnitude() > 0) {
		rigid->addForce(force, PxForceMode::eFORCE);
		force *= 0;
		rigid->addForce(Vector3(0, 0, 0));
	}
	
}

void Solids::move(Vector3 v) {
	if (rigid->getLinearVelocity().magnitude() < 10)
		rigid->addForce(v, PxForceMode::eFORCE);
	//rigid->addForce(v, PxForceMode::eFORCE);
}

Solids::~Solids()
{
	if(item!=nullptr)
	item->release();
}
