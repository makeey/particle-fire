#include "SDL.h"
#include <iostream>
#include <stdio.h>
#include "Screen.h"
#include "Swarm.h"
#include <time.h>
using namespace std;

int main(int argc, char* argv[])
{


	Uint32 color = 0x12345678;
	int trueted = (color & 0xFF000000) >> 26;
	int red = color >> 4;
	cout << (color >> 24) << endl;

	int test;
	cin >> test;
	return 0;



	srand(time(NULL));
	Screen screen;
	if (!screen.init()) {
		cout << "Failed init SDL" << endl;
	}

	Swarm swarm;
	
	bool quit = false;

	while (!quit)
	{
		int tick = SDL_GetTicks();
		screen.clear();
		swarm.update(tick);
		unsigned char green = (unsigned char)((1 + sin(tick * 0.0001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(tick * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(tick * 0.0003)) * 128);

		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixelColor(x, y, red, green, blue);
		}

		screen.boxBlur();

		screen.update();
		
		if (false == screen.processEvent())
		{
			quit = true;
		}

	}

	screen.close();
	return 0;
}