#include "entity.h"

Entity::Entity()
: m_position()
, m_velocity()
, m_destroyed(false)
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

void Entity::setPosition(Vector2f position)
{
	m_position = position;
}

void Entity::setVelocity(float _x, float _y)
{
	m_velocity.x = _x;
	m_velocity.y = _y;
}

void Entity::setVelocity(Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::setSize(float _x, float _y)
{
	m_size.x = _x;
	m_size.y = _y;
}

void Entity::setSize(Vector2f size)
{
	m_size = size;
}

void Entity::setLayer(int layer)
{
	m_layer = layer;
}

Vector2f Entity::getPosition() const
{
	return m_position;
}

Vector2f Entity::getVelocity() const
{
	return m_velocity;
}

Vector2f Entity::getSize() const
{
	return m_size;
}

int Entity::getLayer() const
{
	return m_layer;
}

void Entity::destroy()
{
	m_destroyed = true;
}

void Entity::damage()
{
}

bool Entity::isDestroyed() const
{
	return m_destroyed;
}

bool Entity::collision(Vector2f target)
{
	return false;
}
