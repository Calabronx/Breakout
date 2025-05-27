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

enum Layer
{
	PADDLE,
	BALL,
	BRICK
};

class Entity
{

	public:
		Entity();
		~Entity();

	public:
		virtual bool				isDestroyed() const;
		virtual bool				collision(Vector2f target);
		Vector2f			getPosition() const;
		Vector2f			getVelocity() const;
		Vector2f			getSize() const;
		void				setPosition(float _x, float _y);
		void				setPosition(Vector2f position);
		void				setVelocity(float _x, float _y);
		void				setVelocity(Vector2f velocity);
		void				setSize(float _x, float _y);
		void				setSize(Vector2f size);
		void				setLayer(int layer);
		int				getLayer() const;
		void			destroy();
		void			damage();

	private:
		int				m_lifes;
		int  			m_layer;
 		Vector2f		m_position;
		Vector2f		m_velocity;
		Vector2f		m_size;
		bool 			m_destroyed;


};
#endif

