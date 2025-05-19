#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "brick.h"
#include "paddle.h"

#include <vector>

const int SCREEN_WIDTH = 835;
const int SCREEN_HEIGHT = 768;
const int COL_SIZE = 8;
const int ROW_SIZE = 8;
const int OFFSET = 10;
//const int Y_OFFSET = 30;
const int BRICK_WIDTH = 105;
const int BRICK_HEIGHT = 35;

// classic game class structure
class Game
{
	public:
		Game();
		~Game();

	private:
		void init();
		void update();
		void render();

	public:
		void run();

private:
	std::vector<std::vector<Brick>> m_bricks_vec;
	SDL_Window						*m_window;
	SDL_Renderer					*m_renderer;
	SDL_Surface						*m_surface;
	Paddle							*m_player;
};
#endif

