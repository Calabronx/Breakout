#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "brick.h"
#include "paddle.h"
#include "ball.h"
#include "text.h"

#include <vector>
#include <map>

// game phases
enum Game_Phase
{
	GAME_PHASE_PAUSE,
	GAME_PHASE_START,
	GAME_PHASE_PLAY,
	GAME_PHASE_BALL_OUT,
	GAME_PHASE_GAME_OVER,
	GAME_PHASE_WIN
};

// game state machine
struct Game_State
{
	Game_Phase phase;
	Ball_State ball;
	Paddle_State paddle;
	float 	time;
	int   	points;
	int   	bricks_destroyed_counter;
	int   	cooldown_to_respawn;
	int   	win_screen_time = 0;
	int last_blink_time = 0;
	const int blink_interval = 500;
	bool 	paused_game = false;
	bool 	exit_game = false;
	bool 	win_game = false;
	bool 	start_screen = false;
	bool showText = false;
	bool restart = false;
};

// game class structure
class Game
{
	public:
		Game();
		~Game();

	private:
		void init();
		void reset_game();
		void update(int dt);
		void render(int dt);
		void input(SDL_Event event, std::map<SDL_Keycode, bool> key_map);
		void wait_time_to_respawn();
		void do_collisions(Vector2f &ball_position, Vector2f &paddle_position, Vector2f &ball_velocity);
		bool check_collisions(Entity *first, Entity *second);
		bool check_game_status();

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
	Text								*m_highscore_txt;
	Text								*m_player_lifes_txt;
	Text								*m_screen_pause_txt;
	Text								*m_screen_win_txt;
	Text								*m_loose_win_txt;
};
#endif

