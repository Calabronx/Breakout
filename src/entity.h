#pragma once
#ifndef ENTITY_H
#define ENTITY_H

struct Vector2f
{
	float x;
	float y;
	Vector2f(float _x, float _y) {
		x = _x;
		y = _y;
	}
	Vector2f() {
		x = 0;
		y = 0;
	}
};

class Entity
{

	public:
		Entity();
		~Entity();

	public:
		virtual void				setPosition(float _x, float _y);
		virtual Vector2f			getPosition() const;
		virtual bool				isDestroyed() const;
		void			destroy();
		void			damage();

	private:
		Vector2f		m_position;
		int				m_lifes;

};
#endif

