#pragma once
#include <SDL.h>
#include <stdlib.h>
struct Particle
{

	double x;
	double y;
	Particle();
	~Particle();
	void init();
	double speed;
	double direction;
	void update(int interval);
};

