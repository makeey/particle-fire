#pragma once
#include <SDL.h>
#include <iostream>
class Screen
{
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 400;

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Uint32* buffer1;
	Uint32* buffer2;
public:
	Screen();
	bool init();
	void close();
	bool processEvent();
	void boxBlur();
	void update();
	void setPixelColor(int x, int y, Uint32 red, Uint32 green, Uint32 blue);
	void clear();


};

