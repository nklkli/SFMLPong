module;
#include "pch.h"
export module Ball;
using namespace sf;

export
class Ball
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;
	float m_Speed = 600.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;
public:
	Ball(float startX, float startY);
	const FloatRect& getPosition() const;
	const RectangleShape& getShape();
	float getXVelocity() const;
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void update(Time dt);
};


Ball::Ball(float startX, float startY) : m_Position(startX, startY)
{
	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);
}


const FloatRect& Ball::getPosition() const
{
	return m_Shape.getGlobalBounds();
}

const RectangleShape& Ball::getShape()
{
	return m_Shape;
}

float Ball::getXVelocity() const
{
	return m_DirectionX;
}


void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}
void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;
}
void Ball::reboundBottom()
{
	m_Position.y = 0;
	m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
}


void Ball::update(Time dt)
{
	// Update the ball's position
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
	// Move the ball
	m_Shape.setPosition(m_Position);
}