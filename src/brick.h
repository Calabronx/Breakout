#pragma once
#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "colors.h"

const int WIDTH = 55;
const int HEIGHT = 20;
const int OFFSET = 10;
const int WALL_OFFSET_X = 20;
const int WALL_OFFSET_Y = 180;

class Brick : public Entity
{
	public:
		Brick();
		~Brick();

	public:
		void draw(SDL_Renderer* renderer, Color color_line, const int col, const int row);
};
#endif 

