#include "entity.h"

Entity::Entity()
: m_position(0.0f, 0.0f)
{
}

Entity::~Entity()
{
}

void Entity::setPosition(float _x, float _y)
{
	m_position.x = _x;
	m_position.y = _y;
}

Vector2f Entity::getPosition() const
{
	return m_position;
}

void Entity::destroy()
{
}

void Entity::damage()
{
}

bool Entity::isDestroyed() const
{
	return false;
}
