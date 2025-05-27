#include "game.h"

#include <iostream>
#include <map>
#include "colors.h"

const int SCREEN_WIDTH = 805;
const int SCREEN_HEIGHT = 1000;
const int COL_SIZE = 14;
const int ROW_SIZE = 8;
const int RIGHT_LIMIT = SCREEN_WIDTH - 50;
const int LEFT_LIMIT = 20;
const int PADDLE_VELOCITY = 10 * 1;
Game::Game()
	: m_bricks_vec(ROW_SIZE, std::vector<Brick>(COL_SIZE))
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

	SDL_UpdateWindowSurface(m_window);

}

int bricks_destroyed_counter = 0;
bool collision = false;
bool Game::check_collisions(Entity *first, Entity *second)
{
	Vector2f first_size = first->getSize();
	Vector2f first_pos = first->getPosition();
	Vector2f second_size = second->getSize();
	Vector2f second_pos = second->getPosition();

	if (first_pos.x + first_size.x >= second_pos.x && second_pos.x + second_size.x >= first_pos.x  
		&& first_pos.y + first_size.y >= second_pos.y && second_pos.y + second_size.y >= first_pos.y)
	{
		// std::cout << "COLLISION !" << std::endl;
		if (second->getLayer() == PADDLE)
		{
			std::cout << "COLLISION PADDLE\n";
		}

		return true;
	}

	return false;
}

float velocity = 5;
const int max_velocity = 7;
bool brick_collision = false;
bool expulse_ball = false;
void Game::update()
{
	Vector2f ball_position = m_ball->getPosition();
	Vector2f ball_velocity = m_ball->getVelocity();
	Vector2f paddle_position = m_player->getPosition();

	ball_position.x += ball_velocity.x * velocity;
	ball_position.y += ball_velocity.y * velocity;

	if (ball_position.x <= LEFT_LIMIT || ball_position.x >= RIGHT_LIMIT)
	{
		ball_velocity.x = -ball_velocity.x;
		if(ball_position.x < LEFT_LIMIT)
		{
			std::cout << "ball trapped";
			ball_position.x = LEFT_LIMIT + 2;
		}
		brick_collision = false;
	}

	if (ball_position.y < 0 || ball_position.y > SCREEN_HEIGHT)
	{
		ball_velocity.y = -ball_velocity.y;
		brick_collision = false;
	}

	bool paddle_collision = false;
	if (check_collisions(m_ball, m_player))
	{
		ball_velocity.y = -ball_velocity.y;

		if(velocity >= max_velocity)
		{
			velocity = max_velocity;
		} else {
			velocity *= 1.02f;
			std::cout << "BALL velocity  : " << velocity << std::endl;
		}

		brick_collision = false;
		expulse_ball = false;
		m_ball->setPosition(ball_position.x, ball_position.y-10);

		paddle_collision = true;
	}

	for (int row = 0; row < m_bricks_vec.size(); row++)
		{
			for (int col = 0; col < m_bricks_vec[row].size(); col++)
			{
				if(!m_bricks_vec[row][col].isDestroyed())
				{
					if (check_collisions(m_ball, &m_bricks_vec[row][col]) && !m_bricks_vec[row][col].isDestroyed() && !brick_collision)
					{
						bricks_destroyed_counter++;
						ball_velocity.y = -ball_velocity.y;
						m_ball->setPosition(ball_position.x + 10, ball_position.y + 10);
						m_bricks_vec[row][col].destroy();
						brick_collision = true;
						if(velocity >= max_velocity)
						{
							velocity = max_velocity;
						} else {
							velocity *= 1.02f;
							std::cout << "BALL velocity  : " << velocity << std::endl;
						}
						std::cout << "BRICK  x: " << m_bricks_vec[row][col].getPosition().x << " y: " << m_bricks_vec[row][col].getPosition().y << std::endl;
					} else if (check_collisions(m_ball, &m_bricks_vec[row][col]) && !expulse_ball) {
						expulse_ball = true;
						m_ball->setPosition(ball_position.x, ball_position.y + 100);
					}
				}
			}
	}
	
	
	if(!paddle_collision) {
		m_ball->setPosition(ball_position);
	}
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

inline void render_limits(SDL_Renderer *renderer, const int posX, const int posY)
{
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = 20;
	rect.h = SCREEN_HEIGHT;

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

	render_limits(m_renderer, 1, 0);
	render_limits(m_renderer, SCREEN_WIDTH - 20, 0);

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
