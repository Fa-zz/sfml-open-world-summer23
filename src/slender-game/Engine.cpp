#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Night In a Forest", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Engine::initLight() {
    // create a light source
    lightPtr = new candle::RadialLight();
    lightPtr->setBeamAngle(90);
    lightPtr->setRange(300);
    lightPtr->setFade(false);

    fogPtr = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(0.f,0.f), sf::Vector2f(1500.f,1500.f));
    fogPtr->setAreaColor(sf::Color::Black);

}

void Engine::initPlayer() {
    player.setSize(sf::Vector2f(25.f, 25.f));
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
    initLight();
    initObjects();
    initView();
}

Engine::~Engine() {
    delete window;
    delete lightPtr;
    delete fogPtr;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.move(-4.0f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.move(4.0f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.move(0.f, -4.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.move(0.f, 4.0f);
    }

}

void Engine::update() {
    pollEvents();
    updatePlayer();

    // Calculate midpoint of player, then set lightPtr equal to
    sf::Vector2f rectanglePosition = player.getPosition();
    sf::Vector2f rectangleSize = player.getSize();
    sf::Vector2f playerMidpoint(rectanglePosition.x + rectangleSize.x / 2.f,
                            rectanglePosition.y + rectangleSize.y / 2.f);

    lightPtr->setPosition(playerMidpoint - sf::Vector2f(5.f, 5.f));
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