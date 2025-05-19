#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#include "entity.h"

const int P_WIDTH = 100;
const int P_HEIGHT = 30;
const int INITIAL_POS_X = 380;
const int INITIAL_POS_Y = 700;

class Paddle : public Entity
{
	public:
					Paddle();
					~Paddle();

	public:
		void		draw(SDL_Renderer* renderer);
					
	private:
		void		setPaddlePosition(int x, int y);

	public:
		virtual		void setPosition(float _x, float _y);
		virtual		Vector2f getPosition();

	private:
		Vector2f	m_position;
};

#endif
