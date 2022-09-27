#include "Proyectile.h"

Proyectile::Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir)
{
	switch (currentShotType) {
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(dir * 200); // 35 m/s
		setAcceleration({ 0.0f, -1.0f, 0.0f });
		setDamping(0.99);
		setRender({ 1,.84,0,1 });
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		setVelocity(dir * 400);
		setAcceleration({ 0.0f, -20.0f, 0.0f });
		setDamping(0.99f);
		setRender({ 1,.84,0,1 });
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(dir * 100);
		setAcceleration({ 0.0f, 0.6f, 0.0f }); // floats
		setDamping(0.9f);
		setRender({ 1,.55,0,1 });
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(dir * 1000); // No gravity
		setAcceleration({ 0.0f, 0.0f, 0.0f });
		setDamping(0.99f);
		setRender({ 1,0,0,1 });
		break;
	}
	setPosition(pos);
	//startTime = GetLastFrame();
	//type = currentShotType;
}

void Proyectile::setProyectileType()
{
	//	switch (currentShotType) {
	//	case PISTOL:
	//		shot->particle.setMass(2.0f); // 2.0 Kg
	//		shot->particle.setVelocity(0.0f, 0.0f, 35.0f); // 35 m/s
	//		shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);
	//		shot->particle.setDamping(0.99f);
	//		break;
	//	case ARTILLERY:
	//		shot->particle.setMass(200.0f); // 200.0 Kg
	//		shot->particle.setVelocity(0.0f, 30.0f, 40.0f);
	//		shot->particle.setAcceleration(0.0f, -20.0f, 0.0f);
	//		shot->particle.setDamping(0.99f);
	//		break;
	//	case FIREBALL:
	//		shot->particle.setMass(1.0f); // 1.0 Kg
	//		shot->particle.setVelocity(0.0f, 0.0f, 10.0f);
	//		shot->particle.setAcceleration(0.0f, 0.6f, 0.0f); // floats
	//		shot->particle.setDamping(0.9f);
	//		break;
	//	case LASER:
	//		shot->particle.setMass(0.1f); // almost no weight
	//		shot->particle.setVelocity(0.0f, 0.0f, 100.0f); // No gravity
	//		shot->particle.setAcceleration(0.0f, 0.0f, 0.0f);
	//		shot->particle.setDamping(0.99f);
	//		break;
	//	}
	//	shot->particle.setPosition(0.0f, 1.5f, 0.0f);
	//	shot->startTime = GetLastFrame();
	//	shot->type = currentShotType;
}
