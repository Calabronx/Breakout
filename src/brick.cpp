#include "Brick.h"

#include <iostream>

Brick::Brick()
{
	m_rect.w = WIDTH;
	m_rect.h = HEIGHT;
}

Brick::~Brick()
{
}

SDL_Rect& Brick::getBrickRectangle()
{
	return m_rect;
}

void Brick::setBrickPosition(int x, int y)
{
	m_rect.x = x;
	m_rect.y = y;
}

void Brick::draw(SDL_Renderer* renderer, Color color_line, const int col, const int row)
{
	SDL_Rect rect;
	rect.x = m_position.x;
	rect.y = m_position.y;
	rect.w = WIDTH;
	rect.h = HEIGHT;

	Vector2f brick_position = {};
	brick_position.x = 0 + col * WIDTH;
	brick_position.y = row * HEIGHT + 10;

	m_position = brick_position;

	SDL_SetRenderDrawColor(renderer, color_line.r, color_line.g, color_line.b, color_line.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

