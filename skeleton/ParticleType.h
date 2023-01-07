#pragma once
#include "core.hpp"
#include "ColorHSV.h"

enum particleShape { Sphere, box, capsule };

class particleType {
public:
	Vector3 vel;
	Vector3 ac;
	float damp;
	float mass;
	float remainingTime;
	physx::PxTransform pose;
	Vector3 size;
	hsv col;
	Vector4 color;
	particleShape s;
};
class Pistol : public particleType {
public:
	Pistol(Vector3 dir, Vector3 pos, int rt) {
		mass = 0.20f;
		vel = dir * 35;
		ac = { 0.0f, -1.0f, 0.0f };
		damp = 0.99;
		remainingTime = rt;
		size = { 1.0,0,0 };
		col = { 0.0f,0.0f,0.75f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };
		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};
class Artillery : public particleType {
public:
	Artillery(Vector3 dir, Vector3 pos, int rt) {
		mass = 2.0f;
		vel = dir * 100;
		ac = { 0.0f, -200.0f, 0.0f };
		damp = 0.99;
		remainingTime = rt;
		size = { 3.0,0,0 };

		col = { 0.0f,0.0f,0.0f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};
class Fireball : public particleType {
public:
	Fireball(Vector3 dir, Vector3 pos, int rt) {
		mass = 0.1f;
		vel = dir * 100;
		ac = { 0.0f, 6.0f, 0.0f };
		damp = 0.9;
		remainingTime = rt;
		size = { 1.5,0,0 };

		col = { 32.0f,1.0f,0.65f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};
class Laser : public particleType {
public:
	Laser(Vector3 dir, Vector3 pos, int rt) {
		mass = 0.1f;
		vel = dir * 400;
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.9;
		remainingTime = rt;
		size = { 0.5,0,0 };

		col = { 357.0f,1.0f,0.48f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};
class Agua : public particleType {
public:
	Agua() {
		mass = 1.0f;
		vel = { 0.1,100,0.1 };
		ac = { 0.0f, -0.5f, 0.0f };
		damp = 0.9;
		remainingTime = 200;
		size = { 1.5,0,0 };

		col = { 186.0f,0.77f,0.68f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0,-10.0,0.0 };
		s = particleShape::Sphere;
	}
};
class Nube : public particleType {
public:
	Nube() {
		mass = 1.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.8f;
		remainingTime = 10;
		size = { 0.2f,0.0f,0.0f };

		col = { 214.0f,0.5f,0.92f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-10.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class Suelo : public particleType {
public:
	Suelo() {
		mass = 0.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.0f;
		remainingTime = 0;
		size = { 1000.0f,1.0f,1000.0f };

		col = { 153.0f,1.0f,0.9f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-0.1, 0.0 };
		s = particleShape::box;
	}
};
class PresetFirework : public particleType {
public:
	PresetFirework(int rT, Vector3 pos) {
		mass = 1.0f;
		vel = { 0.0f,100.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.5f;
		remainingTime = rT;
		size = { 1.0f,0.0f,0.0f };

		col = { 357.0f,1.0f,0.5f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform (pos);
		s = particleShape::Sphere;
	}
};
class FireworkHeart : public particleType {
public:
	FireworkHeart(int rT, Vector3 pos) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { 0.5f,0.0f,0.0f };

		col = { 357.0f,1.0f,0.7f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform(pos);
		s = particleShape::Sphere;
	}
};
class RandomFireworks : public particleType {
public:
	RandomFireworks(int rT, Vector3 _color, float _s, Vector3 pos) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { _s ,0.0f,0.0f };

		col = { _color.x,_color.y,_color.z };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform(pos);
		s = particleShape::Sphere;
	}
};
class BatFireworks : public particleType {
public:
	BatFireworks(int rT, Vector3 pos) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { 0.5f ,0.0f,0.0f };

		col = { 53.0f ,0.93f,0.54f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform(pos);
		s = particleShape::Sphere;
	}
};
class GravityParticle1 : public particleType {
public:
	GravityParticle1(Vector3 pos, int rt) {
		mass = 0.001f;
		vel = { 0,0,0 };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.99;
		remainingTime = rt;
		size = { 1.0,0,0 };
		col = { 67.0f,0.93f,0.95f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };
		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};
class forceActionRateParticle : public particleType {
public:
	forceActionRateParticle(float radius, Vector3 pos) {
		mass = 0.0f;
		vel = { 0,0,0 };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.99;
		remainingTime = 0;
		size = { radius,0,0 };
		col = { 353.0f,1.0f,0.47f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,0.4 };
		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};

class RigidBox : public particleType {
public:
	RigidBox(Vector3 pos) {
		mass = 0.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0;
		remainingTime = 1e6;
		size = { 10,5,10.0 };

		col = { 238.0f,0.93f,0.9f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x, pos.y, pos.z };
		s = particleShape::box;
	}
};

class MuelleParticula : public particleType {
public:
	MuelleParticula(Vector3 pos) {
		mass = 10.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.99;
		remainingTime = 1e6;
		size = {5,0,0 };

		col = {63.0f,0.93f,0.8f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};

class MuelleParticula1 : public particleType {
public:
	MuelleParticula1(Vector3 pos) {
		mass = 2.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.99;
		remainingTime = 1e6;
		size = { 5,0,0 };

		col = { 205.0f,0.93f,0.8f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x,pos.y, pos.z };
		s = particleShape::Sphere;
	}
};

class Liquid : public particleType {
public:
	Liquid(Vector3 pos) {
		mass = 0.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0;
		remainingTime = 1e6;
		size = { 50,0.1,50.0 };

		col = { 165.0f,0.93f,0.70f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x, pos.y, pos.z };
		s = particleShape::box;
	}
};

class Barquito : public particleType {
public:
	Barquito(Vector3 pos) {
		mass = 20.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.9;
		remainingTime = 1e6;
		size = { 10,10,10 };

		col = {200.0f,0.6f,1.0f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ pos.x, pos.y, pos.z };
		s = particleShape::box;
	}
};
class Lluvia1 : public particleType {
public:
	Lluvia1() {
		mass = 1.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.8f;
		remainingTime = 100;
		size = { 1.5f,0.0f,0.0f };

		col = { 214.0f,0.5f,0.92f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-10.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class Lluvia2 : public particleType {
public:
	Lluvia2() {
		mass = 0.1f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.8f;
		remainingTime = 100;
		size = { 0.7f,0.0f,0.0f };

		col = { 214.0f,0.4f,0.50f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-10.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class Lluvia3 : public particleType {
public:
	Lluvia3() {
		mass = 3.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.8f;
		remainingTime = 100;
		size = { 3.0f,0.0f,0.0f };

		col = { 220.0f,0.7f,1.0f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-10.0, 0.0 };
		s = particleShape::Sphere;
	}
};