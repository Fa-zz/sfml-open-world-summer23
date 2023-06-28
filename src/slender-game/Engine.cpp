#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920,1080), "View, Light, OOP", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Engine::initPlayer() {
    player.setSize(sf::Vector2f(50.f, 50.f));
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
    initObjects();
    initView();
}

Engine::~Engine() {
    delete window;
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
}

// RENDER FUNCTIONS
void Engine::render() {
    mainView.setCenter(player.getPosition());

    // Draw

    // Draw light, fog
    // fog.clear();
    // fog.draw(light);
    // fog.display();
    // sf::Color myColor(74,103,65);
    // window.clear(myColor);
    window->clear();


    window->setView(mainView);
    // window.draw(background);
    window->draw(object);

    // window.draw(fog);
    window->draw(player);

    // Draw UI
    window->setView(window->getDefaultView());
    window->draw(UIElem);

    // Finished drawning
    window->display();
}