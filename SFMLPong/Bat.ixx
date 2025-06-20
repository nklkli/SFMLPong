module;
#include "pch.h"
export module Bat;
using namespace sf;

export
class Bat
{
	Vector2f m_Position;
	// A RectangleShape object
	RectangleShape m_Shape;
	float m_Speed = 600.0f;
	bool m_MovingRight = false;
	bool m_MovingLeft = false;
public:
	Bat(float startX, float startY);
	const FloatRect& getPosition() const;
	RectangleShape& getShape();
	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	void update(Time dt);
};



// This the constructor and it is called 
// when we create an object
Bat::Bat(float startX, float startY) : m_Position(startX, startY)
{
	m_Shape.setSize({ 50, 5 });
	m_Shape.setPosition(m_Position);
}

const FloatRect& Bat::getPosition() const
{
	return m_Shape.getGlobalBounds();
}

RectangleShape& Bat::getShape()
{
	return m_Shape;
}

void Bat::moveLeft()
{
	m_MovingLeft = true;
}

void Bat::moveRight()
{
	m_MovingRight = true;
}


void Bat::stopLeft()
{
	m_MovingLeft = false;
}


void Bat::stopRight()
{
	m_MovingRight = false;
}


void Bat::update(Time dt)
{
	if (m_MovingLeft) {
		m_Position.x -= m_Speed * dt.asSeconds();
	}
	if (m_MovingRight) {
		m_Position.x += m_Speed * dt.asSeconds();
	}
	m_Shape.setPosition(m_Position);
}