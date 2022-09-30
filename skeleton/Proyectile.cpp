#include "Proyectile.h"

Proyectile::Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir)
{
	switch (currentShotType) {
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(dir * 35); // 35 m/s
		setAcceleration({ 0.0f, -1.0f, 0.0f });
		setDamping(0.99);
		setRender(particleType::Sphere, 1.0,0.0,0.0,  { 1,.84,0,1 });
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		setVelocity(dir * 40);
		setAcceleration({ 0.0f, -200.0f, 0.0f });
		setDamping(0.99f);
		setRender(particleType::Sphere, 3.0, 0.0, 0.0,  { 1,.84,0,1 });
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(dir * 10);
		setAcceleration({ 0.0f, 6.0f, 0.0f }); // floats
		setDamping(0.9f);
		setRender(particleType::Sphere, 1.5, 0.0, 0.0,  { 1,.84,0,1 });
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(dir * 1000); // No gravity
		setAcceleration({ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		setRender(particleType::Sphere, 0.8, 0.0, 0.0, { 1,.84,0,1 });
		break;
	}
	setPosition(pos);
	//startTime = GetLastFrame();
	//type = currentShotType;
}

