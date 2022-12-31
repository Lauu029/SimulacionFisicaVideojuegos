#include "Solids.h"

Solids::Solids(Vector3 _meanPos, Vector3 _meanVel,
	PxShape* _gShape, PxRigidDynamic* rig, SolidType _t)
{
	type = _t;
	pos = _meanPos;
	vel = _meanVel;
	rigid = rig;
	rig->userData = this;
	rigid->setLinearVelocity((vel));
	rigid->setAngularVelocity(PxVec3(0, 0, 0));
	gShape = _gShape;
	rigid->attachShape(*gShape);
	rigid->setMassSpaceInertiaTensor({ type.size.y * type.size.z, 
		type.size.x * type.size.z, type.size.x * type.size.y });
	if (type.render)
	item = new RenderItem(gShape, rigid, type.col);
	time = 0;
	force = { 0, 0, 0 };

	gst = type.gst;
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
	if (type.fade) {
		type.colorHsv.v += 0.1;
		rgb transf = hsv2rgb(type.colorHsv);
		type.col = Vector4( transf.r,transf.g, transf.b ,1.0);
		item->color = type.col;
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
