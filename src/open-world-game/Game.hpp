#pragma once

#include <iostream>

#include "Block.hpp"

class Game {
private:
    // Variables

    // Window view
    sf::RenderWindow* window;
    sf::View mainView;
    float viewSpeed;

    // Player, elems
    sf::RectangleShape player;
    sf::RectangleShape UIElem;

    // Private functions
    void initWindow();
    void initPlayer();
    void initView();

public:
    Game();
    virtual ~Game();

    // Functions
    void run();

    void update();
    void render();
};