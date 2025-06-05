#pragma once
#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "constants.h"

struct Ball_State
{
	const int 	initial_velocity = INITIAL_BAll_VELOCITY;
	const int 	max_velocity = MAX_BAll_VELOCITY;
	float 		velocity;
	bool 		brick_collision 		= false;
	bool 		expulse			 		= false;
	bool 		change_velocity 		= false;
	bool 		first_paddle_collision  = false;
	bool 		increase_velocity  		= false;

};

class Ball : public Entity
{
	public: 
		Ball();
		~Ball();

	public:
		// void draw(SDL_Renderer* renderer, Color color);
		void draw(SDL_Renderer* renderer);
		// mover la bola
		void moveBall();
		void count_brick();
		virtual bool collision(Vector2f target);

	private:
		float 	m_velocity;
		int 	m_brick_destroyed_counter;

};
#endif

