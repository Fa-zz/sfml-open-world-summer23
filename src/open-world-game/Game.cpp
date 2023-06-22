#include "Game.hpp"

// Pirvate functions
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Practice", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() {
    player.setSize(sf::Vector2f(50.f, 50.f));
    player.setPosition(500.f,500.f);

    UIElem.setSize(sf::Vector2f(300.f,50.f));
}

void Game::initView() {
    mainView.setSize(1920,1080);
}

// Constructor, destructor
Game::Game() {
    initWindow();
    initPlayer();
    initView();
}

Game::~Game() {
    delete window;
}

// Functions
void Game::run() {

    while (window->isOpen()) {
        update();
        render();
    }
}

void Game::update() {
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

void Game::render() {
    window->clear();

    // Draw stuff
    window->setView(mainView);
    window->draw(player);

    // UI
    window->setView(window->getDefaultView());
    window->draw(UIElem);

    window->display();
}