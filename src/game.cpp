#include "game.h"

#include <iostream>
#include <map>
#include <chrono>
#include <thread>

#include "colors.h"

const int SCREEN_WIDTH = 805;
const int SCREEN_HEIGHT = 1000;
const int COL_SIZE = 14;
const int ROW_SIZE = 8;
const int RIGHT_LIMIT = SCREEN_WIDTH - 50;
const int LEFT_LIMIT = 20;
const int PADDLE_VELOCITY = 10 * 1;
const int COOLDOWN_TO_RESPAWN = 2;
const int BRICKS_AMOUNT = 112;

Game::Game()
	: m_bricks_vec(ROW_SIZE, std::vector<Brick>(COL_SIZE))
	, m_game_state()
	, m_renderer()
	, m_surface()
{
	init();
}

Game::~Game()
{
}

void Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize the window\n";
		return;
	}

	m_window = SDL_CreateWindow("Brekaout",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT, 0);

	if (m_window == nullptr)
	{
		std::cout << "Failed to create the window\n";
		return;
	}

	if (!m_window)
	{
		SDL_Log("Window pointer is null!");
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return;
	}

	m_surface = SDL_GetWindowSurface(m_window);

	if (m_surface == nullptr)
	{
		std::cout << "Failed to get the surface from the window\n";
		return;
	}

	m_player = new Paddle();
	m_ball = new Ball();
	m_ball->setPosition(m_ball->getPosition().x, m_ball->getPosition().y + 2);
	
	m_game_state = new Game_State();
	m_game_state->phase = GAME_PHASE_PLAY; // deberia ser start screen
	m_game_state->ball.velocity = m_game_state->ball.initial_velocity;
	m_game_state->cooldown_to_respawn = COOLDOWN_TO_RESPAWN;

	SDL_UpdateWindowSurface(m_window);

}

bool Game::check_collisions(Entity *first, Entity *second)
{
	Vector2f first_size = first->getSize();
	Vector2f first_pos = first->getPosition();
	Vector2f second_size = second->getSize();
	Vector2f second_pos = second->getPosition();

	if (first_pos.x + first_size.x >= second_pos.x && second_pos.x + second_size.x >= first_pos.x  
		&& first_pos.y + first_size.y >= second_pos.y && second_pos.y + second_size.y >= first_pos.y)
	{
		// // std::cout << "COLLISION !" << std::endl;
		// if (second->getLayer() == PADDLE)
		// {
		// 	std::cout << "COLLISION PADDLE\n";
		// }

		return true;
	}

	return false;
}

void Game::update()
{
	Vector2f ball_position = m_ball->getPosition();
	Vector2f ball_velocity = m_ball->getVelocity();
	Vector2f paddle_position = m_player->getPosition();

	ball_position.x += ball_velocity.x * m_game_state->ball.velocity;
	ball_position.y += ball_velocity.y * m_game_state->ball.velocity;

	if(m_player->isDestroyed() || m_game_state->bricks_destroyed_counter >= BRICKS_AMOUNT)
	{
		m_game_state->phase = GAME_PHASE_GAME_OVER;
		return;
	}

	if (m_game_state->bricks_destroyed_counter == 14 || m_game_state->bricks_destroyed_counter == 28 || m_game_state->bricks_destroyed_counter == 56
		|| m_game_state->bricks_destroyed_counter >= 80)
	{
		m_game_state->ball.increase_velocity = true;
	}

	if(m_game_state->phase == GAME_PHASE_BALL_OUT)
	{
		for (int i = m_game_state->cooldown_to_respawn; i > 0; --i)
		{	
			std::cout << i << " seconds remaining" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		m_game_state->phase = GAME_PHASE_PLAY;
		m_game_state->ball.velocity = m_game_state->ball.initial_velocity;
		m_game_state->ball.first_paddle_collision = false;
		m_player->damage(); 
		m_player->setPosition(380, 960);
	}

	if (m_game_state->phase != GAME_PHASE_PLAY)
	{
		return;
	}

	if (ball_position.x <= LEFT_LIMIT || ball_position.x >= RIGHT_LIMIT)
	{
		ball_velocity.x = -ball_velocity.x;
		if(ball_position.x < LEFT_LIMIT)
		{
			ball_position.x = LEFT_LIMIT + 2;
		}
		// m_game_state->ball.brick_collision = false;
		m_game_state->ball.first_paddle_collision = false;
	}

	if (ball_position.y < 0 || ball_position.y <= 185.00  || ball_position.y > SCREEN_HEIGHT)
	{
		if (ball_position.y > SCREEN_HEIGHT)
		{
			m_ball->setPosition(420, 680);
			ball_velocity.x = 0.0f;
			m_ball->setVelocity(ball_velocity);
			m_game_state->ball.change_velocity = false;
			m_game_state->phase = GAME_PHASE_BALL_OUT;
			// m_game_state->ball.brick_collision = false;
			return;	
		}
		if (ball_position.y <= 181.00)
		{
			ball_position.y = 180.00;
			ball_velocity.y = -ball_velocity.y;
			// m_game_state->ball.brick_collision = false;
		} else {
			// ball_velocity.y = -ball_velocity.y;
			// m_game_state->ball.brick_collision = false;
		}
		m_game_state->ball.first_paddle_collision = false;
		m_ball->setPosition(ball_position);

	}

	bool collision_player = check_collisions(m_ball, m_player);
	if (collision_player && !m_game_state->ball.first_paddle_collision)
	{     
		ball_velocity.y = -ball_velocity.y;
		ball_velocity.x = -ball_velocity.x;

		if(m_game_state->ball.velocity >= m_game_state->ball.max_velocity)
		{
			m_game_state->ball.velocity = m_game_state->ball.max_velocity;
		} else {
			if(m_game_state->ball.increase_velocity)
			{
				m_game_state->ball.velocity *= 1.02f;
				std::cout << "BALL velocity  increase: " << m_game_state->ball.velocity << std::endl;
				m_game_state->ball.increase_velocity = false;
			}
		}

		m_game_state->ball.brick_collision = false;
		m_game_state->ball.expulse = false;
		m_ball->setPosition(ball_position.x, ball_position.y - 10);
		if(!m_game_state->ball.change_velocity)
		{
			ball_velocity.x = 1.0f;
			m_ball->setVelocity(ball_velocity);
			m_game_state->ball.change_velocity = true;
		} else {

			m_ball->setVelocity(ball_velocity);
		}

		m_game_state->ball.first_paddle_collision = true;
	} else if (collision_player){
		if (m_game_state->bricks_destroyed_counter >= 15)
			m_game_state->ball.velocity *= 1.02f;

		std::cout << "BALL velocity  : " << m_game_state->ball.velocity << std::endl;
	}

	for (int row = 0; row < m_bricks_vec.size(); row++)
	{
			for (int col = 0; col < m_bricks_vec[row].size(); col++)
			{
				if(!m_bricks_vec[row][col].isDestroyed())
				{
					if (check_collisions(m_ball, &m_bricks_vec[row][col]) && !m_bricks_vec[row][col].isDestroyed() && !m_game_state->ball.brick_collision)
					{
						m_game_state->bricks_destroyed_counter++;
						ball_velocity.y = -ball_velocity.y;
						m_ball->setPosition(ball_position.x + 10, ball_position.y + 10);
						m_bricks_vec[row][col].destroy();
						m_game_state->ball.brick_collision = true;
						m_game_state->ball.first_paddle_collision = false;

						if(m_game_state->ball.velocity >= m_game_state->ball.max_velocity)
						{
							m_game_state->ball.velocity = m_game_state->ball.max_velocity;
						} 
						std::cout << "BRICK  x: " << m_bricks_vec[row][col].getPosition().x << " y: " << m_bricks_vec[row][col].getPosition().y << std::endl;
					} else if (check_collisions(m_ball, &m_bricks_vec[row][col]) && !m_game_state->ball.expulse) {
						m_game_state->ball.expulse = true;
						// ball_velocity.y = -ball_velocity.y;
						m_ball->setPosition(ball_position.x, ball_position.y);
					}
				}
			}
	}

	m_ball->setPosition(ball_position);
	m_ball->setVelocity(ball_velocity);

	if (paddle_position.x >= RIGHT_LIMIT)
	{
		m_player->setPosition(paddle_position.x - 10, paddle_position.y);
	}

	if (paddle_position.x <= LEFT_LIMIT)
	{
		m_player->setPosition(paddle_position.x + 10, paddle_position.y);
	}
	// std::cout << "BALL x: " << ball_position.x << " y: " << ball_position.y << std::endl;

	render();
}

inline Color choose_row_color(int row) {
	switch (row) {
	case 0:
	case 1:
		return RED;
	case 2:
	case 3:
		return ORANGE;
	case 4:
	case 5:
		return GREEN;
	case 6:
	case 7:
		return YELLOW;
	}

	return BLACK;
}

void inline render_brick_wall(SDL_Renderer* renderer, std::vector<std::vector<Brick>>& bricks)
{
	for (int row = 0; row < bricks.size(); row++)
	{
		Color color_line = choose_row_color(row);
		for (int col = 0; col < bricks[row].size(); col++)
		{
			Brick& brick = bricks[row][col];
			if(!brick.isDestroyed())
			{
				brick.draw(renderer, color_line, col, row);
				SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
			}
		}
	}
}

inline void render_limits(SDL_Renderer *renderer, const int width, const int height, const int posX, const int posY)
{
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
}

void Game::render()
{
	SDL_RenderClear(m_renderer);

	m_player->draw(m_renderer);
	m_ball->draw(m_renderer);

	render_brick_wall(m_renderer, m_bricks_vec);

	render_limits(m_renderer, 25, SCREEN_HEIGHT, 0, 0);
	render_limits(m_renderer, 25,SCREEN_HEIGHT , SCREEN_WIDTH - 20, 0);
	render_limits(m_renderer, SCREEN_WIDTH, 60, 0, 0);

	SDL_RenderPresent(m_renderer);
}


void Game::run()
{
	bool exit = false;
	std::map<SDL_Keycode, bool> key_map;
	unsigned int time = SDL_GetTicks();

	while (!exit)
	{
		SDL_Event event;
		unsigned int delta = SDL_GetTicks();
		delta = delta - time;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case	SDL_QUIT:
				exit = true;
				break;
			case	SDL_KEYDOWN:
				key_map[event.key.keysym.sym] = true;
				break;
			case	SDL_KEYUP:
				key_map[event.key.keysym.sym] = false;
				break;
			}
		}

		if(m_game_state->phase == GAME_PHASE_GAME_OVER)
		{
			exit = true;
		}

		if (key_map[SDLK_LEFT])
		{
			m_player->setPosition(m_player->getPosition().x - PADDLE_VELOCITY, m_player->getPosition().y);
		}
		if (key_map[SDLK_RIGHT])
		{
			m_player->setPosition(m_player->getPosition().x + PADDLE_VELOCITY, m_player->getPosition().y);
		}
		if (key_map[SDLK_ESCAPE])
		{
			exit = true;
		}


		update();
	}


	SDL_Quit();
}
