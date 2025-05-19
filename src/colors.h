#pragma once
#ifndef COLORS_H
#define COLORS_H

struct Color {
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};

inline Color color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = a;
	return result;
}

const Color RED = {
	color(0xFF,0x00,0x00,0xFF)
};

const Color ORANGE = {
	color(0xFF,0xA5,0x00,0xFF)
};

const Color GREEN = {
	color(0x00,0x80,0x00,0xFF)
};

const Color YELLOW = {
	color(0xFF,0xFF,0x00,0xFF)
};

const Color BLACK = {
	color(0x00,0x00,0x00,0xFF)
};

const Color WHITE = {
	color(0xFF,0xFF,0xFF,0xFF)
};
#endif