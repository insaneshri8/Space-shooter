#pragma once
#include<SFML/Graphics.hpp>
class Enemy
{

private:
	sf::Sprite m_sprite;
	int type;
	int hp;
	int maxhp;
	int damage;
	float m_speed;
	int points = 0;
	sf::Vector2f direction;
	void InitShape();
	void InitVariables();
	
public:
	Enemy(sf::Vector2f pos);
	Enemy();
	Enemy(sf::Texture* texture , sf::Vector2f pos,  sf::Vector2f dir,  float speed);
	
	const int& getdamage() const;


	~Enemy();
	int& getPoints();

	sf::FloatRect getBounds() const;
	sf::Vector2f getPos();

	void update();
	void render(sf::RenderTarget* target);
};

