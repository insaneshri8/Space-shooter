#pragma once


#include<SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
private:
	Sprite m_Sprite;
	sf::Vector2f direction;
	float m_speed = 5.f;
public:
	Bullet();
	Bullet(sf::Texture* texture, float xPos, float yPos, float dirx, float diry, float speed);
	~Bullet();

	 sf::FloatRect getBounds() const;

	//update and render
	void update();
	void render(sf::RenderTarget* target);

};

