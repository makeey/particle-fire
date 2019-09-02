#include "Screen.h"

Screen::Screen(): window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL), buffer_color(NULL), buffer_color2(NULL)
{
	

}

bool Screen::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL init failed" << std::endl;
	}

	window = SDL_CreateWindow
	("Patricle Fire ", // window's title
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		Screen::SCREEN_WIDTH,
		Screen::SCREEN_HEIGHT, // window's length and height in pixels  
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STATIC,
		Screen::SCREEN_WIDTH,
		Screen::SCREEN_HEIGHT
	);

	if (renderer == NULL)
	{
		std::cout << "Could not create renderer" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	if (texture == NULL)
	{
		std::cout << "Could not create texture" << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}


	buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	buffer_color = new Color[SCREEN_WIDTH * SCREEN_HEIGHT];
	buffer_color2 = new Color [SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	
	return true;
}

void Screen::close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Screen::processEvent()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}
	return true; 
}

void Screen::update()
{
	SDL_UpdateTexture(texture, NULL, buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Screen::setPixelColor(int x, int y, Uint32 red, Uint32 green, Uint32 blue)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	Color colorObject =  Color(red, green, blue);
	buffer_color[(y * SCREEN_WIDTH) + x] = colorObject;
	buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::setPixelColor(int x, int y, Color color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	buffer_color[(y * SCREEN_WIDTH) + x] = color;
	setPixelColor(x, y, color.red, color.green, color.blue);
}
void Screen::clear()
{
	memset(buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void Screen::boxBlur() {
	// Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1.
	Color* temp = buffer_color;
	buffer_color = buffer_color2;
	buffer_color2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
						Color color = buffer_color2[currentY * SCREEN_WIDTH + currentX];


						redTotal += color.red;
						greenTotal += color.green;
						blueTotal += color.blue;
					}
				}
			}

			
			Uint32 red = redTotal / 9;
			Uint32 green = greenTotal / 9;
			Uint32 blue = blueTotal / 9;
			
			setPixelColor(x, y, red, green, blue);
		}
	}
}