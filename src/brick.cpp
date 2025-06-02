#include "Brick.h"

#include <iostream>

const int offset_x = 2;
const int offset_y = 5;

Brick::Brick()
{	
	// set_brick_type(row);
	setLayer(BRICK);
	setSize(WIDTH, HEIGHT);
}

Brick::~Brick()
{
	std::cout << "brick destroyed" << std::endl;
}

void Brick::fill_rect(SDL_Renderer* renderer, int x, int y, int width, int height, Color color)
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

void Brick::set_brick_type(int row) {
	switch (row) {
	case 0:
	case 1:
		m_type = RED;
		return;
	case 2:
	case 3:
		m_type = ORANGE;
		return;
	case 4:
	case 5:
		m_type = GREEN;
		return;
	case 6:
	case 7:
		m_type = YELLOW;
		return;
	}
}

int Brick::getType() const
{
	return m_type;
}

void Brick::draw(SDL_Renderer* renderer, Color color_line, const int col, const int row)
{
	Vector2f brick_position = {};
	brick_position.x = WALL_OFFSET_X + col * WIDTH;
	brick_position.y = WALL_OFFSET_Y + row * HEIGHT;
	setPosition(brick_position);
	int light_color = getType();

	fill_rect(renderer, getPosition().x, getPosition().y, WIDTH - offset_x, HEIGHT - offset_y, color_line);
	fill_rect(renderer, getPosition().x, getPosition().y, WIDTH - offset_x, HEIGHT / 3.5 - offset_y, LIGHT_COLORS[light_color]);
	fill_rect(renderer, getPosition().x, getPosition().y, WIDTH / 8  - offset_x, HEIGHT - offset_y, LIGHT_COLORS[light_color]);
}

