#pragma once


#include"Bullet.h"
#include"Player.h"
#include"Enemy.h"
#include"Enemy2.h"
#include<map>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
class Game
{
	//GUI
	sf::Font font;
	sf::Text point;
	unsigned points;
	void  initGUI();

	sf::Text GameOver;

	//world
	sf::Texture Bg_texture;
	sf::Sprite worldBG;
	void initWorld();
	void initSystem();
	void renderWorld();


public:
	void updateGUI();
	void renderGUI();

	// test gravity failed
private:
	float mass = 20;
	float velocityX = 0.1f;
	float velocityY = 0.0f;

	float a;
	float b;
	float acc;
	float accX;
	float accY;

	void SetPos();


private:

	std::map< std::string, sf::Texture*> e3_Texture;
	std::vector<Enemy2*> enemies3;

	void initEnemy3();

	float spawnTimer3;
	float spawnTimerMax3;



public:

	void InitEnemyTexture3();
	void updateEnemyAndCombat3();


public:
	Game();
	~Game();
	void Run();
	void Update();
	void Render();
	void updateWorld();
	void updateCollision();
	//Init window
	void UpdatePollEvent();
	void updateInput();



public:
	// Player
	void InitPlayer();
	int health = 200;

public:
	// Bullets
	void InitTexture();
	void updatebullet();


private:
	//window
	sf::RenderWindow* m_Window;
	

private:
	//Player
	Player* m_Player = nullptr;
	std::map < std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;


	sf::RectangleShape HpBar;
	sf::RectangleShape HpBarBack;

	//Enemy
private:

	std::map < std::string, sf::Texture*> e_Texture;
	std::vector<Enemy*> enemies;

	void initEnemy();

	float spawnTimer;
	float spawnTimerMax;

	

public:

	void InitEnemyTexture();
	void updateEnemyAndCombat();


	//Enemy 2
private:

	std::map< std::string, sf::Texture*> e2_Texture;
	std::vector<Enemy*> enemies2;

	void initEnemy2();

	float spawnTimer2;
	float spawnTimerMax2;



public:

	void InitEnemyTexture2();
	void updateEnemyAndCombat2();

};

