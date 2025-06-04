#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "colors.h"

const int P_WIDTH = 50;
const int P_HEIGHT = 25;
const int INITIAL_POS_X = 395;
const int INITIAL_POS_Y = 960;
const int LIFES = 5;

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
		void		fill_rect(SDL_Renderer* renderer, int x, int y, int width, int height, Color color);
		void		damage();
		void		movePaddle();	
		void 		restart_lifes();		
		int 		getLifes() const;
	private:
		int			m_lifes;
};

#endif
