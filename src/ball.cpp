#include "ball.h"
#include "colors.h"

Ball::Ball()
{
	setLayer(BALL);
	setPosition(420, 680);
	setVelocity(1.0f, 1.0f);
	setSize(20, 20);
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

	SDL_SetRenderDrawColor(renderer, YELLOW.r, YELLOW.g, YELLOW.b, YELLOW.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

void Ball::moveBall()
{
	//if (collision(

}

bool Ball::collision(Vector2f target)
{
	Vector2f position = getPosition();

	if (position.x > target.x && position.y > target.y)
		return true;

	return false;
}
