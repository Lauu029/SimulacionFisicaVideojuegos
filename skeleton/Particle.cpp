#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acceleration, double dampling,
	particleType t, Vector3 _size, Vector4 _color, double time)
{
	vel = Vel;
	ac = acceleration;
	damp = dampling;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	remainingTime = time;
	type = t;
	size = _size;
	color = _color;

	setRender(t, size, color);
}



Particle::~Particle()
{

	if (renderItem != nullptr) {
		renderItem->release();
		/*DeregisterRenderItem(renderItem);
		renderItem = nullptr;*/
	}
}

void Particle::integrate(double t)
{
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);

	vel += ac * t;

	vel *= powf(damp, t);

	remainingTime--;
}

Vector3 Particle::getPos()
{
	return{ pose.p.x,pose.p.y,pose.p.z };
}

void Particle::setRender(particleType t, Vector3 size, Vector4 color)
{
	switch (t)
	{
	case Sphere:
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size.x)), &pose, color);
		break;
	case box:
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(size.x, size.y, size.z)), &pose, color);
		break;
	case capsule:
		renderItem = new RenderItem(CreateShape(physx::PxCapsuleGeometry(size.x, size.y)), &pose, color);
		break;
	default:
		break;
	}
}
void Particle::setColor(Vector4 _color) {
	color = _color;
	renderItem->color = color;
}

