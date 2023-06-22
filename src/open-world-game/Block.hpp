#pragma once
#include "Block.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Block {
private:

    // Private functions
    void init();

public:
    Block();
    virtual ~Block();

    // Functions
    void update();
    void render(sf::RenderTarget& target);
};