#pragma once
#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Block {
private:
    sf::Sprite sprite;
    sf::Texture texture;

    // Private functions
    void initTexture();
    void initSprite();

public:
    Block();
    virtual ~Block();

    // Functions
    void update();
    void render(sf::RenderTarget& target);
};