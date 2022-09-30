#pragma once
#include <string>
#include "Particle.h"

enum  ShotType { PISTOL, ARTILLERY, FIREBALL, LASER };
class Proyectile : public Particle
{
public:
	Proyectile(ShotType currentShotType, Vector3 pos, Vector3 dir);
private:
};

