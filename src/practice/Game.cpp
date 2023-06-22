#include "Game.hpp"

// Pirvate functions
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Practice", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

// Constructor, destructor
Game::Game() {
    initWindow();
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
        if (e.Event::type == sf::Event::Closed)
            window->close();
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            window->close();
    }
}

void Game::render() {
    window->clear();

    // Draw stuff

    window->display();
}