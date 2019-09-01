#pragma once
#include "Particle.h"
class Swarm
{
public:
	const static int NPARTICLES = 5000;

private:
	Particle* particles;
	int last_tick = 0;

public:
	Swarm();
	virtual ~Swarm();

	void update(int tick);

	const Particle* const getParticles() { return particles; };
};

