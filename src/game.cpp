#include "game.h"

#include <iostream>
#include "colors.h"

Game::Game()
	: m_bricks_vec(8, std::vector<Brick>(8))
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
		SCREEN_HEIGHT,0);

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

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
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

	SDL_UpdateWindowSurface(m_window);

}

void Game::update()
{
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

void inline render_brick_wall(SDL_Renderer* renderer, std::vector<std::vector<Brick>> &bricks)
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		Color color_line = choose_row_color(row);
		for (int col = 0; col < COL_SIZE; col++)
		{
			Brick& brick = bricks[row][col];
			brick.draw(renderer, color_line, col, row);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(m_renderer);

	m_player->draw(m_renderer);
	render_brick_wall(m_renderer, m_bricks_vec);

	SDL_RenderPresent(m_renderer);
}


void Game::run()
{
	bool exit = false;

	while (!exit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case	SDL_QUIT:
						exit = true;
						break;
				case	SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						exit = true;
						break;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						m_player->setPosition(m_player->getPosition().x - 20, m_player->getPosition().y);
						break;
					}
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						m_player->setPosition(m_player->getPosition().x + 20, m_player->getPosition().y);
						break;
					}
			}
		}

		update();
	}

	SDL_Quit();
}
