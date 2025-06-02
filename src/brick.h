#pragma once
#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "colors.h"

const int WIDTH = 55;
const int HEIGHT = 30;
const int OFFSET = 10;
const int WALL_OFFSET_X = 20;
const int WALL_OFFSET_Y = 180;


class Brick : public Entity
{
	enum Brick_Type
	{
		RED,
		ORANGE,
		GREEN,
		YELLOW
	};
	public:
		Brick();
		~Brick();

	private:
		void fill_rect(SDL_Renderer* renderer, int x, int y, int width, int height, Color color);

	public:
		void set_brick_type(int row);
		int getType() const;
		void draw(SDL_Renderer* renderer, Color color_line, const int col, const int row);

	private:
		int m_type;
};
#endif 

