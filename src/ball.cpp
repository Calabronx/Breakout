
#include "ball.h"
#include "colors.h"
#include <random>

Ball::Ball()
{
	setLayer(BALL);
	setPosition(410, INITIAL_BALL_Y);
	setVelocity(0.0f, 1.0f);
	setSize(20, 20);
	m_brick_destroyed_counter = 0;
	
}

Ball::~Ball()
{
}

void Ball::draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = getPosition().x;
	rect.y = getPosition().y;
	rect.w = getSize().x;
	rect.h = getSize().y;

	if(m_brick_destroyed_counter >= 28)
	{
		const int colorCount = sizeof(LIGHT_COLORS) / sizeof(LIGHT_COLORS[0]);
		Color randomColor = LIGHT_COLORS[rand() % colorCount];
		SDL_SetRenderDrawColor(renderer, randomColor.r, randomColor.g, randomColor.b, randomColor.a);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderDrawRect(renderer, &rect);
	} else {
		SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderDrawRect(renderer, &rect);
	}

}

void Ball::moveBall()
{
	//if (collision(

}

void Ball::count_brick()
{
	++m_brick_destroyed_counter;
}

bool Ball::collision(Vector2f target)
{
	Vector2f position = getPosition();

	if (position.x > target.x && position.y > target.y)
		return true;

	return false;
}
