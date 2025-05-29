#pragma once
#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "entity.h"

const int MAX_BAll_VELOCITY = 9;
const int INITIAL_BAll_VELOCITY = 5;

struct Ball_State
{
	const int 	initial_velocity = INITIAL_BAll_VELOCITY;
	const int 	max_velocity = MAX_BAll_VELOCITY;
	float 		velocity;
	bool 		brick_collision 		= false;
	bool 		expulse			 		= false;
	bool 		change_velocity 		= false;
	bool 		first_paddle_collision  = false;

};

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

