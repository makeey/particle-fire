#include "Color.h"

Color::Color(): red(0), green(0), blue(0)
{
}

Color::Color(unsigned char _red, unsigned char _green, unsigned char _blue)
{
	red = _red;
	green = _green;
	blue = _blue;
}