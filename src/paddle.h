#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#include "entity.h"

const int P_WIDTH = 50;
const int P_HEIGHT = 25;
const int INITIAL_POS_X = 410;
const int INITIAL_POS_Y = 960;
const int LIFES = 6;

struct Paddle_State
{
	bool moving_right = false;
	bool moving_left = false;
	int lifes = LIFES;
};

class Paddle : public Entity
{
	public:
					Paddle();
					~Paddle();

	public:
		void		draw(SDL_Renderer* renderer);
		void		damage();
		void		movePaddle();			
		int 		getLifes() const;
	private:
		int			m_lifes;
};

#endif
