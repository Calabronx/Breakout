#include "Brick.h"

#include <iostream>

Brick::Brick()
{	
	setLayer(BRICK);
	setSize(WIDTH, HEIGHT);
}

Brick::~Brick()
{
	std::cout << "brick destroyed" << std::endl;
}

void Brick::draw(SDL_Renderer* renderer, Color color_line, const int col, const int row)
{
	Vector2f brick_position = {};
	brick_position.x = WALL_OFFSET_X + col * WIDTH;
	brick_position.y = WALL_OFFSET_Y + row * HEIGHT;
	setPosition(brick_position);

	const int offset_x = 2;
	const int offset_y = 5;

	SDL_Rect rect;
	rect.x = getPosition().x;
	rect.y = getPosition().y;
	rect.w = WIDTH - offset_x;
	rect.h = HEIGHT - offset_y;

	SDL_SetRenderDrawColor(renderer, color_line.r, color_line.g, color_line.b, color_line.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

