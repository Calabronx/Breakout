#pragma once
#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "entity.h"


class Ball : public Entity
{
	public: 
		Ball();
		~Ball();

	public:
		void draw(SDL_Renderer* renderer);
		// mover la bola
		void moveBall();
		virtual bool collision(Vector2f target);

};
#endif

