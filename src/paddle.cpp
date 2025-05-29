#include "paddle.h"
#include "colors.h"

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
	if (m_lifes <= 0 || isDestroyed())
	{
		destroy();
		return;
	}

	m_lifes-=1;
}
