#include "Game.h"

// Private functions
void Game::initVariables()
{
    window = nullptr;

    // Game logic
    endGame = false;
    points = 0;
    health = 20;
    enemySpawnTimerMax = 20.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 5;
    mouseHeld = false;
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
    enemy.setFillColor(sf::Color::Cyan);
    // enemy.setOutlineColor(sf::Color::Green);
    // enemy.setOutlineThickness(1.f);
}

void Game::initFonts()
{
    font.loadFromFile("assets/Fonts/Dosis-Light.ttf");
}

void Game::initText()
{
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("NONE");
}

// Constructors and destructors
Game::Game()
{
    initVariables();
    initWindow();
    initFonts();
    initText();
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

const bool Game::getEndGame() const
{
    return endGame;
}

// Functions
void Game::spawnEnemy()
{
    /*
        @return void

        Spawn enemies and sets their types and colors. Spawns them at random positions.
        -Sets a random position.
        -Sets a random color.
        -Adds enemy to the vector.
    */

    enemy.setPosition(static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)), 0.f);

    // Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        enemy.setSize(sf::Vector2f(10.f, 10.f));
        enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        enemy.setSize(sf::Vector2f(30.f, 30.f));
        enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        enemy.setSize(sf::Vector2f(50.f, 50.f));
        enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        enemy.setSize(sf::Vector2f(70.f, 70.f));
        enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Green);
        break;
    default:
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Yellow);
        break;
    }

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
    mousePosView = window->mapPixelToCoords(mousePosWindow);
};

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << points << "\n"
       << "Health: " << health << "\n";
    uiText.setString(ss.str());
}

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

    // Moving and updating enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        // Move the enemies
        enemies[i].move(0.f, 5.f);

        // If the enemy is past the bottom of the screen
        if (enemies[i].getPosition().y > window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health -= 1;
            std::cout << "Health: " << health << '\n';
        }
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mouseHeld == false)
        {
            mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < enemies.size() && deleted == false; i++)
            {
                if (enemies[i].getGlobalBounds().contains(mousePosView))
                {
                    // Gain points
                    if (enemies[i].getFillColor() == sf::Color::Magenta)
                        points += 10.f;
                    else if (enemies[i].getFillColor() == sf::Color::Blue)
                        points += 7.f;
                    else if (enemies[i].getFillColor() == sf::Color::Cyan)
                        points += 5.f;
                    else if (enemies[i].getFillColor() == sf::Color::Red)
                        points += 3.f;
                    else if (enemies[i].getFillColor() == sf::Color::Green)
                        points += 1.f;
                    std::cout << "Points: " << points << '\n';

                    // Delete the enemy

                    deleted = true;
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        mouseHeld = false;
    }
}

void Game::update()
{
    pollEvents();

    if (endGame == false)
    {
        updateMousePositions();

        updateText();

        updateEnemies();
    }

    // Endgame condition
    if (health <= 0)
        endGame = true;
}

void Game::renderEnemies(sf::RenderTarget &target)
{
    // Rendering all the enemies
    for (auto &e : enemies)
    {
        target.draw(e);
    }
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(uiText);
}

void Game::render()
{
    window->clear();

    // Draw game objects
    renderEnemies(*window);

    renderText(*window);

    window->display();
}