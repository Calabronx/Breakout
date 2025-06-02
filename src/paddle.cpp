#include "paddle.h"
#include "colors.h"

#include <iostream>

Paddle::Paddle()
	: m_lifes(LIFES)
{
	setLayer(PADDLE);
	setPosition(INITIAL_POS_X, INITIAL_POS_Y);
	setSize(P_WIDTH, P_HEIGHT);
}

Paddle::~Paddle()
{
}

void Paddle::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = getPosition().x;
	rect.y = getPosition().y;
	rect.w = getSize().x;
	rect.h = getSize().y;

	SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
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
