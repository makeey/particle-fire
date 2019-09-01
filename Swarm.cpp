#include "Swarm.h"


Swarm::Swarm() {
	particles = new Particle[NPARTICLES];

}

Swarm::~Swarm() {
	delete[] particles;
}

void Swarm::update(int tick)
{
	int interval = last_tick - tick;
	for (int i = 0; i < Swarm::NPARTICLES; i++) {
		particles[i].update(interval);
	}
	last_tick = tick;
}

