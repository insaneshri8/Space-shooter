#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
class Player
{
private:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	// variable
	float m_Speed;
	float coolDown;
	float coolDownMax;

	//hp
	int hp;
	int hpmax;

	// Init Player
	void initVaribles();
	void InitPlayer();


public:
	Player();
	~Player();

	void move(sf::Vector2f direction);


	// modifiers
	void setPos(sf::Vector2f pos);
	void setPos(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);


	//accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& gethp() const;
	const int& gethpmax() const;


	const bool isAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);

};

