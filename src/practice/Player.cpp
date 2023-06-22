#include "Player.hpp"

void Block::initTexture() {
    // load texture from file
}

void Block::initSprite() {
    // set the texture to the sprite
    sprite.setTexture(texture);
}

Block::Block() {
    initTexture();
    initSprite();
}

Block::~Block() {

}

// Functions
void Block::update() {

}

void Block::render(sf::RenderTarget& target) {
    target.draw(sprite);
}