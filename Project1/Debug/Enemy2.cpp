#include "Enemy2.h"


void Enemy2::InitVaribales()
{
	m_speed = sf::Vector2f(2.f, 2.f);
}

Enemy2::Enemy2()
{
	this->InitVaribales();
}


Enemy2::Enemy2(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f speed)
{
	m_sprite.setTexture(*texture);
	m_sprite.setScale(0.4f, 0.4f);
	m_sprite.setPosition(pos);
	direction = dir;
	m_speed = speed;
}

Enemy2::~Enemy2()
{

}

int& Enemy2::getPoints()
{
	// TODO: insert return statement here
	points += 15;
	return points;
}

sf::FloatRect Enemy2::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Enemy2::getPos()
{
	return m_sprite.getPosition();
}



void Enemy2::update()
{
	m_sprite.move(direction.x * m_speed.x  , direction.y * m_speed.y);
}

void Enemy2::render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}
