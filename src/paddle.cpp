#include "paddle.h"
#include "colors.h"

#include <iostream>
Paddle::Paddle()
	: m_lifes(LIFES)
{
	setLayer(PADDLE);
	setPosition(INITIAL_PLAYER_X, INITIAL_PLAYER_Y);
	setSize(P_WIDTH, P_HEIGHT);
}

Paddle::~Paddle()
{
}

void Paddle::fill_rect(SDL_Renderer* renderer, int x, int y, int width, int height, Color color)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

void Paddle::draw(SDL_Renderer* renderer)
{
	fill_rect(renderer, getPosition().x, getPosition().y, P_WIDTH , P_HEIGHT , BLUE);
	fill_rect(renderer, getPosition().x, getPosition().y, P_WIDTH , P_HEIGHT / 3.5 , LIGHT_COLORS[4]);
	fill_rect(renderer, getPosition().x, getPosition().y, P_WIDTH / 8  , P_HEIGHT, LIGHT_COLORS[4]);
}

void Paddle::damage()
{
	m_lifes--;
	if (m_lifes <= 0 || isDestroyed())
	{
		destroy();
		return;
	}

	std::cout << "Paddle::damage()" << std::endl;
}

void Paddle::restart_lifes()
{
	reborn();
	m_lifes = 6;
}

int Paddle::getLifes() const
{
	return m_lifes;
}

void Paddle::movePaddle()
{
	// if (paddle_position.x >= RIGHT_LIMIT)
	// {
	// 	m_player->setPosition(paddle_position.x - 10, paddle_position.y);
	// }

	// if (paddle_position.x <= LEFT_LIMIT)
	// {
	// 	m_player->setPosition(paddle_position.x + 10, paddle_position.y);
	// }


}
