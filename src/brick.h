#pragma once
#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "colors.h"

const int WIDTH = 100;
const int HEIGHT = 30;

class Brick : public Entity
{
	public:
		Brick();
		~Brick();

	public:
		SDL_Rect& getBrickRectangle();
		void setBrickPosition(int x, int y);
		void draw(SDL_Renderer* renderer, Color color_line, const int col, const int row);

	private:
		SDL_Rect	m_rect;
		Vector2f	m_position;

};
#endif 

