#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acceleration, double dampling)
{
	vel = Vel;
	ac = acceleration;
	damp = dampling;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);

}



Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);

	vel += ac * t;

	vel *= powf(damp, t);

}

Vector3 Particle::getPos()
{
	return{ pose.p.x,pose.p.y,pose.p.z };
}

void Particle::setRender(Vector4 color)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose,color);
	RegisterRenderItem(renderItem);
}
