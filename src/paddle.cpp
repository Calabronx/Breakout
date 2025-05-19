#include "paddle.h"
#include "colors.h"

Paddle::Paddle()
{
	m_position.x = INITIAL_POS_X;
	m_position.y = INITIAL_POS_Y;
}

Paddle::~Paddle()
{
}

void Paddle::setPaddlePosition(int x, int y)
{
}

void Paddle::setPosition(float _x, float _y)
{
	m_position.x = _x;
	m_position.y = _y;
}

Vector2f Paddle::getPosition()
{
	return m_position;
}

void Paddle::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = m_position.x;
	rect.y = m_position.y;
	rect.w = P_WIDTH;
	rect.h = P_HEIGHT;

	SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

