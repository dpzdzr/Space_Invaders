#include "../inc/Game.h"

// Private functions
void Game::initVariables()
{
    window = nullptr;

    // Game logic
    points = 0;
    enemySpawnTimerMax = 1000.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 5;
}
void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;

    window = new sf::RenderWindow(videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    enemy.setPosition(10.f, 10.f);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Cyan);
    // enemy.setOutlineColor(sf::Color::Green);
    // enemy.setOutlineThickness(1.f);
}

// Constructors and destructors
Game::Game()
{
    initVariables();
    initWindow();
    initEnemies();
}

Game::~Game()
{
    delete window;
}

// Accessors
const bool Game::running() const
{
    return window->isOpen();
}

// Functions
void Game::spawnEnemy()
{
    /*
        @return void

        Spawn enemies and sets their color and positions.
        -Sets a random position.
        -Sets a random color.
        -Adds enemy to the vector.
    */

    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
        0.f);

    enemy.setFillColor(sf::Color::Green);

    // Spawn the enemy
    enemies.push_back(enemy);
}

void Game::pollEvents()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::updateMousePositions()
{   

    mousePosWindow = sf::Mouse::getPosition(*window);
   // mousePosView = window->mapPixelToCoords();
};

void Game::updateEnemies()
{
    /*
        @return void

        Updates the enemy spawn timer and spawns enemies, when the total amount
        of enemies is smaller than the maximum.
        Moves the enemies downwards.
        Removes the enemies at the edge of the screen. //TODO
    */

    // Update the timer for enemy spawning
    if (enemies.size() < maxEnemies)
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }
        else
            enemySpawnTimer += 1.f;

    // Move the enemies
    for (auto &e : enemies)
    {
        e.move(0.f, 1.f);
    }
}

void Game::update()
{
    pollEvents();

    updateMousePositions();

    updateEnemies();
}

void Game::renderEnemies()
{
    // Rendering all the enemies
    for (auto &e : enemies)
    {
        window->draw(e);
    }
}

void Game::render()
{
    window->clear();

    // Draw game objects
    renderEnemies();

    window->display();
}