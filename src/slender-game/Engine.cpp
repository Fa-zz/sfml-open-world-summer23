#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Night In a Forest", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Engine::initVars() {
    gameAreaSize = sf::Vector2f(15000.f, 15000.f);
    gameAreaBoundsPtr = new sf::FloatRect(sf::Vector2f(0.f,0.f), gameAreaSize);
    playerMoveSpeed = 5.f;
    playerNewPosition = sf::Vector2f(0,0);
}

void Engine::initLight() {
    // create a light source
    lightPtr = new candle::RadialLight();
    lightPtr->setBeamAngle(90);
    lightPtr->setRange(300);
    lightPtr->setFade(false);

    fogPtr = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(0.f,0.f), gameAreaSize);
    std::cout << "Fog ptr global bounds: " << fogPtr->getGlobalBounds().height << " " << fogPtr->getGlobalBounds().width << std::endl;
    fogPtr->setAreaColor(sf::Color::Black);

}

void Engine::initPlayer() {
    player.setRadius(25.f);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(500.f,500.f);
}

void Engine::initObjects() {
    initPlayer();

    object.setSize(sf::Vector2f(100.f,100.f));
    object.setPosition(800.f,800.f);

    UIElem.setSize(sf::Vector2f(300.f,50.f));
}

void Engine::initView() {
    mainView.setSize(1920,1080);
}

// CONSTRUCTOR, DESTRUCTOR
Engine::Engine() {
    initWindow();
    initVars();
    initLight();
    initObjects();
    initView();
}

Engine::~Engine() {
    delete window;
    delete lightPtr;
    delete fogPtr;
    delete gameAreaBoundsPtr;
}

// RUN, UPDATE, POLL EVENTS FUNCTIONS
void Engine::run() {

    while (window->isOpen()) {
        update();
        render();
    }
}

void Engine::pollEvents() {
    sf::Event e;
    while(window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed) {
            std::cout << "WINDOW CLOSED" << std::endl;
            window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
            std::cout << "WINDOW CLOSED, ESCAPE" << std::endl;
            window->close();
        }
    }
}

void Engine::updatePlayer() {
    playerMovement = sf::Vector2f(0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        playerMovement.y -= playerMoveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        playerMovement.y += playerMoveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        playerMovement.x -= playerMoveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        playerMovement.x += playerMoveSpeed;

    playerNewPosition = player.getPosition() + playerMovement;
    if (gameAreaBoundsPtr->contains(playerNewPosition))
        player.setPosition(playerNewPosition);
        else {
            std::cout << "ADJUSTING PLAYER POS, EXCEEDING BOUNDS" << std::endl;
            // Adjust player position if it exceeds the game area bounds
            if (playerNewPosition.x < gameAreaBoundsPtr->left)
                playerNewPosition.x = gameAreaBoundsPtr->left;
            else if (playerNewPosition.x > gameAreaBoundsPtr->left + gameAreaBoundsPtr->width)
                playerNewPosition.x = gameAreaBoundsPtr->left + gameAreaBoundsPtr->width;

            if (playerNewPosition.y < gameAreaBoundsPtr->top)
                playerNewPosition.y = gameAreaBoundsPtr->top;
            else if (playerNewPosition.y > gameAreaBoundsPtr->top + gameAreaBoundsPtr->height)
                playerNewPosition.y = gameAreaBoundsPtr->top + gameAreaBoundsPtr->height;

            player.setPosition(playerNewPosition);
        }
}

void Engine::update() {
    pollEvents();
    updatePlayer();

    // Calculate the midpoint of the circle, then set lightPtr equal to
    circlePosition = player.getPosition();
    float circleRadius = player.getRadius();
    sf::Vector2f playerMidpoint(circlePosition.x + circleRadius, circlePosition.y + circleRadius);

    lightPtr->setPosition(playerMidpoint - sf::Vector2f(3.f,3.f));
}

// RENDER FUNCTIONS
void Engine::render() {
    mainView.setCenter(player.getPosition());
    // Draw

    // Draw light, fog
    fogPtr->clear();
    fogPtr->draw(*lightPtr);
    fogPtr->display();

    sf::Color myColor(74,103,65);
    window->clear(myColor);

    window->setView(mainView);
    window->draw(object);

    window->draw(*fogPtr);
    window->draw(player);

    // Draw UI
    window->setView(window->getDefaultView());
    window->draw(UIElem);

    // Finished drawning
    window->display();
}