#include "Enemy.h"

void Enemy::InitShape()
{

}

void Enemy::InitVariables()
{
	 this->type = 0;
	 this->maxhp = 10;
	 this->hp = 0;
	 this->damage = 1;
	 this->points = 5;
	 this->m_speed = 5.f;
}

Enemy::Enemy()
{
	InitVariables();
}

Enemy::Enemy(sf::Vector2f pos)
{

	m_sprite.setPosition(pos);
}

Enemy::Enemy(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f dir, float speed)
{
	m_sprite.setTexture(*texture);
	m_sprite.setScale(0.5f, 0.5f);
	m_sprite.setPosition(pos);
	direction = dir;
	m_speed = speed;

}

Enemy::~Enemy()
{
	
}




sf::FloatRect Enemy::getBounds() const
{
	return this->m_sprite.getGlobalBounds();
}

const int& Enemy::getdamage() const
{
	return this->damage;
}

void Enemy::update()
{
	m_sprite.move(direction * m_speed);
}

sf::Vector2f Enemy::getPos()
{
	// TODO: insert return statement here
	return (this->m_sprite.getPosition());
}

 int& Enemy::getPoints() 
{
	// TODO: insert return statement here
	points = points + 10;
	return points;
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}
