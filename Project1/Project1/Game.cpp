#include "Game.h"

void Game::initGUI()
{
    if (!font.loadFromFile("Font/arial.ttf"))
        std::cout << "failed to load font ";

    point.setFont(font);
    point.setCharacterSize(20);
    point.setFillColor(sf::Color::White);
    point.setString("test");

    GameOver.setFont(font);
    point.setCharacterSize(50);
    GameOver.setPosition(m_Window->getSize().x / 2, m_Window->getSize().y / 2);
    GameOver.setFillColor(sf::Color::Red);
    GameOver.setString("Game Over !");
    
    //init player gui
    HpBar.setSize(sf::Vector2f(300.f, 25.f));
    HpBar.setFillColor(sf::Color::Red);
    HpBar.setPosition(sf::Vector2f(20.f, 20.f));
    HpBarBack = HpBar; 
    HpBarBack.setFillColor(sf::Color(25,25,25,200));

}

void Game::initWorld()
{
    if (!this->Bg_texture.loadFromFile("texture/space2.jpg"))
    {
        std::cout << " Failed to BackGround texture ";

    }
    worldBG.setTexture(Bg_texture);
}

void Game::initSystem()
{
    points = 0;
}

void Game::renderWorld()
{
    m_Window->draw(worldBG);
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss <<" Points :" << this->points;
    point.setString(ss.str());

    //update player gui
    m_Player->setHp(5);
    float hpPercent = static_cast<float>(m_Player->gethp()) / m_Player->gethpmax();
    HpBar.setSize(sf::Vector2f(300.f * hpPercent, HpBar.getSize().y));
}

void Game::renderGUI()
{
   // m_Window->draw(point);
    m_Window->draw(HpBarBack);
    m_Window->draw(HpBar);
}

void Game::SetPos()
{
    for (size_t i =0; i<enemies3.size(); i++)
    {
        a = m_Player->getPos().x - enemies3[i]->getPos().x;
        b = m_Player->getPos().y - enemies3[i]->getPos().y;
        acc = (mass) / (a * a + b * b);
        accX = (acc * a)  / (sqrt(a * a + b * b));
        accY = (acc * b) / (sqrt(a * a + b * b));

        velocityX += accX;
        velocityY += accY;
    }
}

void Game::initEnemy3()
{
    spawnTimerMax3 = 500.f;
    this->spawnTimer3 = spawnTimerMax3;
}

void Game::InitEnemyTexture3()
{
    // initilize  enemy texture
    e3_Texture["Enemy3"] = new sf::Texture();
    e3_Texture["Enemy3"]->loadFromFile("texture/comet.png");
}

void Game::updateEnemyAndCombat3()
{
    spawnTimer3 += 0.5f;
    if (this->spawnTimer3 >= spawnTimerMax3)
    {
        enemies3.push_back(new Enemy2(e3_Texture["Enemy3"],
            sf::Vector2f(rand() % m_Window->getSize().x - 20.f, -50.f),
            sf::Vector2f(0.f, 1.0f), sf::Vector2f(velocityX , velocityY + 10)));
        spawnTimer3 = 0.f;

    }

    unsigned counter = 0;
    for (auto* enemy : enemies3)
    {
        if (enemy->getBounds().intersects(m_Player->getBounds()))
        {
            health -= 10;
            delete enemies3.at(counter);
            enemies3.erase(enemies3.begin() + counter);
            std::cout << " player health " << health << std::endl;

        }

        ++counter;
    }

    for (int i = 0; i < this->enemies3.size(); i++)
    {
        bool remove = false;
        enemies3[i]->update();


        for (size_t k = 0; k < bullets.size() && !remove; k++)
        {

            if (this->bullets[k]->getBounds().intersects(this->enemies3[i]->getBounds()))
            {
                points += this->enemies3[i]->getPoints();
                this->bullets.erase(bullets.begin() + k);
                this->enemies3.erase(enemies3.begin() + i);
                std::cout << " Enemy 3 remove by hitting " << std::endl;
                remove = true;
            }
        }


        // remove enemy at bottom
        if (!remove)
        {
            if (enemies3[i]->getBounds().top > m_Window->getSize().y)
            {
                enemies3.erase(enemies3.begin() + i);
                std::cout << enemies3.size() << " delete 3 enemy " << std::endl;
                remove = true;
            }
        }
    }


}

Game::Game()
{
    //player;
    
    m_Window = new sf::RenderWindow(sf::VideoMode(1000, 900), "Game" , sf::Style::Close);
    m_Window->setFramerateLimit(120);
    m_Window->setVerticalSyncEnabled(false);

    initWorld();
    initSystem();
    InitPlayer();
    InitTexture();
    InitEnemyTexture();
    initEnemy();
    initEnemy2();
    InitEnemyTexture2();
    initEnemy3();
    InitEnemyTexture3();
    SetPos();
    initGUI();

}

Game::~Game()
{
    delete m_Window;
    delete m_Player;


    // send address of every texture we created and its deleted
    for (auto& i : textures)
    {
        delete i.second;
    }

    // delete from vector
    for (auto *i : bullets)
    {
        delete i;
    }


    // delete enemy
    for (auto& i : e_Texture)
    {
        delete i.second;
    }

    for (auto* i : enemies)
    {
        delete i;
      

    }

    // delete enemy2

    for (auto& i : e2_Texture)
    {
        delete i.second;
    }

    for (auto* i : enemies2)
    {
        delete i;


    }

    //delete enemy3
    for (auto& i : e3_Texture)
    {
        delete i.second;
    }

    for (auto* i : enemies3)
    {
        delete i;


    }
}

void Game::Run()
{

    while (m_Window->isOpen())
    {
        Update();
        Render();
        
    }
}

void Game::Update()
{
    UpdatePollEvent();
    updateInput();
    m_Player->update();
    updateCollision();
    updatebullet();
    updateEnemyAndCombat();
    updateEnemyAndCombat2();
    updateEnemyAndCombat3();
    SetPos();
    updateGUI();
    updateWorld();

}

void Game::Render()
{
    m_Window->clear();

    renderWorld();
    // Draw here
    m_Player->render(*m_Window);
    //Bullet Draw
    for (auto* i : bullets)
    {
        i->render(m_Window);
     }
    // enemy
    
    for (auto* i : enemies)
    {

        i->render(m_Window);
    }

    // enemy2
    for (auto* i : enemies2)
    {
        i->render(m_Window);
    }

    // enemy3
    for (auto* i : enemies3)
    {
        i->render(m_Window);
    }


    if (health <= 0)
    {
        m_Window->draw(GameOver);
        exit(0);
    }
    renderGUI();
    m_Window->display();
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
    // left player collision
    if (m_Player->getBounds().left < 0.f)
    {
        m_Player->setPos(0.f, m_Player->getBounds().top);
    }
    else if (m_Player->getBounds().left + m_Player->getBounds().width >= m_Window->getSize().x)
    {
        m_Player->setPos(m_Window->getSize().x - m_Player->getBounds().width, m_Player->getBounds().top);
    }

    //top
    if (m_Player->getBounds().top < 0.f)
    {
        this->m_Player->setPos(m_Player->getBounds().left, 0.f);
    }
    else if (m_Player->getBounds().top + m_Player->getBounds().height >= m_Window->getSize().y)
    {
        m_Player->setPos( m_Player->getBounds().left , m_Window->getSize().y - m_Player->getBounds().height);
    }

}

void Game::InitPlayer()
{
    m_Player = new Player();
}

void Game::InitTexture()
{
    // initiliza texture
    textures["BULLET"] = new sf::Texture();
    textures["BULLET"]->loadFromFile("texture/bullet.png");

}

void Game::initEnemy()
{
    spawnTimerMax = 50.f;
    this->spawnTimer = spawnTimerMax;

}

void Game::InitEnemyTexture()
{
        // initilize  enemy texture
    e_Texture["Enemy"] = new sf::Texture();
    e_Texture["Enemy"]->loadFromFile("texture/asteroid1.png");

}

void Game::updateEnemyAndCombat()
{
    spawnTimer += 0.5f;
    if (this->spawnTimer >= spawnTimerMax)
    {
        enemies.push_back(new Enemy(e_Texture["Enemy"], 
            sf::Vector2f(rand() % m_Window->getSize().x-20.f , -100.f),
            sf::Vector2f(0.f, 1.f), 3.f));
        spawnTimer = 0.f;

    }

    unsigned counter = 0;
    for (auto* enemy : enemies)
    {
        if (enemy->getBounds().intersects(m_Player->getBounds()))
        {
            health -= 10;
            delete enemies.at(counter);
            enemies.erase(enemies.begin() + counter);
            std::cout << " player health " << health << std::endl;

        }

        ++counter;
    }


    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool remove = false;
        enemies[i]->update();


        for (size_t k = 0; k < bullets.size() && !remove; k++)
        {
            if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
            {
                points += this->enemies[i]->getPoints();
                this->bullets.erase(bullets.begin() + k);
                this->enemies.erase(enemies.begin() + i);
                std::cout << " Enemy remove by hitting " << std::endl;
                remove = true;
            }
          
        }


        // remove enemy at bottom
        if (!remove)
        {
            if (enemies[i]->getBounds().top > m_Window->getSize().y)
            {
                enemies.erase(enemies.begin() + i);
                std::cout << enemies.size() << " delete enemy " << std::endl;
                remove = true;
            }
        }
    }


    
}

void Game::initEnemy2()
{

    spawnTimerMax2 = 200.f;
    this->spawnTimer2 = spawnTimerMax2;

}

void Game::InitEnemyTexture2()
{
    // initiliza texture
    e2_Texture["Enemy2"] = new sf::Texture();
    e2_Texture["Enemy2"]->loadFromFile("texture/asteroids_image.png");
}

void Game::updateEnemyAndCombat2()
{
    spawnTimer2 += 0.5f;
    if (this->spawnTimer2 >= spawnTimerMax2)
    {
        enemies2.push_back(new Enemy(e2_Texture["Enemy2"],
            sf::Vector2f(rand() % m_Window->getSize().x - 20.f, -100.f),
            sf::Vector2f(0.f, 1.f), 3.f));
        spawnTimer2 = 0.f;

    }

    unsigned counter = 0;
    for (auto* enemy : enemies2)
    {
        if (enemy->getBounds().intersects(m_Player->getBounds()))
        {
            health -= 10;
            delete enemies2.at(counter);
            enemies2.erase(enemies2.begin() + counter);
            std::cout << " player health " << health << std::endl;

        }

        ++counter;
    }



    for (int i = 0; i < this->enemies2.size(); i++)
    {
        bool remove = false;
        enemies2[i]->update();


        for (size_t k = 0; k < bullets.size() && !remove; k++)
        {
            if (this->bullets[k]->getBounds().intersects(this->enemies2[i]->getBounds()))
            {
               // points += this->enemies[i]->getPoints();
                this->bullets.erase(bullets.begin() + k);
                this->enemies2.erase(enemies2.begin() + i);
                std::cout << " Enemy remove by hitting " << std::endl;
                remove = true;
            }
        }


        // remove enemy at bottom
        if (!remove)
        {
            if (enemies2[i]->getBounds().top > m_Window->getSize().y)
            {
                enemies2.erase(enemies2.begin() + i);
                std::cout << enemies2.size() << " delete enemy 2 " << std::endl;
                remove = true;
            }
        }
    }

}




void Game::updatebullet()
{
    unsigned counter = 0;
    for (auto* bull : bullets)
    {
        bull->update();
         
        // bullet culling the   (top of screen)
        if (bull->getBounds().top + bull->getBounds().height < 0.f)
        {
            //delete 
            delete bullets.at(counter); // at counter position
            bullets.erase(bullets.begin() + counter);
            --counter;

            std::cout << " Delete bullets " << std::endl;
        }   
        ++counter;
    }

    
}

void Game::UpdatePollEvent()
{
    sf::Event ev;
    while (m_Window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            m_Window->close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            m_Window->close();
    }

}

void Game::updateInput()
{
    // move the player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))   // -x direction
        m_Player->move(sf::Vector2f(-1.f, 0.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))   // x+ direction
        m_Player->move(sf::Vector2f(1.f, 0.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))   // -y direction
        m_Player->move(sf::Vector2f(0.f, -1.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))   // +y direction
        m_Player->move(sf::Vector2f(0.f, 1.f));


    //Bullet

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_Player->isAttack())
    {
        bullets.push_back(new Bullet(textures["BULLET"],
            this->m_Player->getPos().x + this->m_Player->getBounds().width/2, this->m_Player->getPos().y,
            0.f, -1.f, 10.f));


    }
    
    
       
    
}

