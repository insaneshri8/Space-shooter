#include "Player.h"

void Player::initVaribles()
{
	m_Speed = 4.f;
	coolDownMax = 5.f;
	coolDown = coolDownMax;

	hpmax = 50;
	hp = hpmax;
}

void Player::InitPlayer()
{
	if (!m_Texture.loadFromFile("texture/spacecraft1.png"))
	{
		std::cout << " Failed to load texture ! ";
	}
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setScale(0.5f, 0.5f);
}

Player::Player()
{

	InitPlayer();
	initVaribles();
    
}

Player::~Player()
{

}

void Player::move(sf::Vector2f direction)
{
	m_Sprite.move(direction * m_Speed);
}

const sf::Vector2f& Player::getPos() const
{
	// TODO: insert return statement here
	return this->m_Sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->m_Sprite.getGlobalBounds();
}

const int& Player::gethp() const
{
	return hp;

}

const int& Player::gethpmax() const
{
	return hpmax;
}



void Player::setPos(sf::Vector2f pos)
{
	m_Sprite.setPosition(pos);
}

void Player::setPos(const float x, const float y)
{
	m_Sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (hp < 0)
		hp = 0;
}

const bool Player::isAttack()
{
	if (coolDown >= coolDownMax)
	{
		coolDown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (coolDown < coolDownMax)
		coolDown += 0.5f;
}

void Player::update()
{
	updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(m_Sprite);
}
