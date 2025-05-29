#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "brick.h"
#include "paddle.h"
#include "ball.h"

#include <vector>

// game phases
enum Game_Phase
{
	GAME_PHASE_START,
	GAME_PHASE_PLAY,
	GAME_PHASE_BALL_OUT,
	GAME_PHASE_GAME_OVER
};

// game state machine
struct Game_State
{
	Game_Phase phase;
	Ball_State ball;
	int   points;
	int   bricks_destroyed_counter;
	int   cooldown_to_respawn;
	float time;
};

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
	Game_State							*m_game_state;
};
#endif

