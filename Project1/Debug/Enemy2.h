#pragma once

#include<SFML/Graphics.hpp>

class Enemy2
{
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_speed;
	sf::Vector2f direction;

	int points;
	void InitVaribales();

public:
	Enemy2();
	
	Enemy2(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f speed);
	~Enemy2();
	int& getPoints();
	sf::FloatRect getBounds() const;
	sf::Vector2f getPos();
	void update();
	void render(sf::RenderTarget* target);

};

