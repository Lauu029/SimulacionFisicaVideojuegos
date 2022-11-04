#include "Particle.h"
#include <iostream>

Particle::Particle(particleType p, bool b)
{
	vel = p.vel;
	ac = p.ac;
	damp = p.damp;
	pose = p.pose;
	mass = p.mass;
	inverse_mass = 1 / mass;
	remainingTime = p.remainingTime;
	shape = p.s;
	size = p.size;
	color = p.color;
	type = p;

	if (b)
		setRender(shape, size, color);
	else renderItem = nullptr;
}

Particle::~Particle()
{
	if (renderItem != nullptr) {
		renderItem->release();
	}
}

void Particle::integrate(double t)
{
	if (inverse_mass <= 0.0f) return;

	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);

	Vector3 totalAcceleration= ac;

	totalAcceleration+= force * inverse_mass;

	vel += ac * t;

	vel *= powf(damp, t);

	remainingTime--;
	
	clearForce();
}

Vector3 Particle::getPos()
{
	return{ pose.p.x,pose.p.y,pose.p.z };
}

void Particle::setRender(particleShape s, Vector3 size, Vector4 color)
{
	switch (s)
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

Firework::Firework(particleType p, int nH, FireworkType _t, bool b) : Particle(p, b)
{
	numHijos = nH;
	t = _t;
	_isActive = true;
}

void Firework::explode()
{
	_isActive = false;
}

