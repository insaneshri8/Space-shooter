#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float xPos , float yPos, float dirx , float diry, float speed)
{
	this->m_Sprite.setTexture(*texture); // dereference to pointer
	this->m_Sprite.setPosition(xPos , yPos);
	this->m_Sprite.setScale(0.2f, 0.2f);
	this->direction.x = dirx;
	this->direction.y = diry;
	this->m_speed = speed;
}

Bullet::~Bullet()
{

}

sf::FloatRect Bullet::getBounds() const
{
	return m_Sprite.getGlobalBounds();
}

void Bullet::update()
{
	//move
	m_Sprite.move(m_speed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(m_Sprite);
}
