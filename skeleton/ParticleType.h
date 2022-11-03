#pragma once
#include "core.hpp"
#include "ColorHSV.h"

enum particleShape { Sphere, box, capsule };

class particleType {
public:
	Vector3 vel;
	Vector3 ac;
	double damp;
	double mass;
	double remainingTime;
	physx::PxTransform pose;
	Vector3 size;
	hsv col;
	Vector4 color;
	particleShape s;
};
class Pistol : public particleType {
public:
	Pistol(Vector3 dir, Vector3 pos) {
		mass = 2.0f;
		vel = dir * 35;
		ac = { 0.0f, -1.0f, 0.0f };
		damp = 0.99;
		remainingTime = 100;
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
	Artillery(Vector3 dir, Vector3 pos) {
		mass = 200.0f;
		vel = dir * 100;
		ac = { 0.0f, -200.0f, 0.0f };
		damp = 0.99;
		remainingTime = 100;
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
	Fireball(Vector3 dir, Vector3 pos) {
		mass = 1.0f;
		vel = dir * 100;
		ac = { 0.0f, 6.0f, 0.0f };
		damp = 0.9;
		remainingTime = 150;
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
	Laser(Vector3 dir, Vector3 pos) {
		mass = 0.1f;
		vel = dir * 400;
		ac = { 0.0f, 0.0f, 0.0f };
		damp = 0.9;
		remainingTime = 60;
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
		remainingTime = 60;
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
		mass = 1.0f;
		vel = { 0.0f,0.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.0f;
		remainingTime = 0;
		size = { 200.0f,1.0f,200.0f };

		col = { 118.0f,1.0f,0.7f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,-0.1, 0.0 };
		s = particleShape::box;
	}
};
class PresetFirework : public particleType {
public:
	PresetFirework(int rT) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.5f;
		remainingTime = rT;
		size = { 1.0f,0.0f,0.0f };

		col = { 357.0f,1.0f,0.5f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,0.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class FireworkHeart : public particleType {
public:
	FireworkHeart(int rT) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { 0.5f,0.0f,0.0f };

		col = { 357.0f,1.0f,0.7f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,0.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class RandomFireworks : public particleType {
public:
	RandomFireworks(int rT, Vector3 _color, float _s) {
		mass = 1.0f;
		vel = { 0.0f,30.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { _s ,0.0f,0.0f };

		col = { _color.x,_color.y,_color.z };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,0.0, 0.0 };
		s = particleShape::Sphere;
	}
};
class BatFireworks : public particleType {
public:
	BatFireworks(int rT) {
		mass = 1.0f;
		vel = { 0.0f,10.0f,0.0f };
		ac = { 0.0f,0.0f, 0.0f };
		damp = 0.9f;
		remainingTime = rT;
		size = { 0.5f ,0.0f,0.0f };

		col = { 53.0f ,0.93f,0.54f };
		rgb rgb = hsv2rgb(col);
		color = { rgb.r,rgb.g,rgb.b,1.0 };

		pose = physx::PxTransform{ 0.0 ,0.0, 0.0 };
		s = particleShape::Sphere;
	}
};