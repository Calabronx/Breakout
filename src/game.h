#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "brick.h"
#include "paddle.h"
#include "ball.h"

#include <vector>

// game class structure
class Game
{
	public:
		Game();
		~Game();

	private:
		void init();
		void update();
		void render();
		bool check_collisions(Entity *first, Entity *second);

	public:
		void run();

private:
	std::vector<std::vector<Brick>>		m_bricks_vec;
	SDL_Window							*m_window;
	SDL_Renderer						*m_renderer;
	SDL_Surface							*m_surface;
	Paddle								*m_player;
	Ball								*m_ball;
};
#endif

