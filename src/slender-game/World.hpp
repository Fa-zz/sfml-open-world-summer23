#pragma once

// For random number generation
#include <cstdlib>
#include <iostream>
#include <time.h>

#include <vector>

#include "CustomColors.hpp"
#include "Data.hpp"

class World {
private:
    int m_numTrees, m_numRocks;

    void generateTrees();
    void generateRocks();
public:
    // Variables
    sf::Vector2f m_gameAreaSize;

    // Helper functions
    float randomFloat();
    int randomInt(int a, int b);
    float randomFloat(int a, int b);
    bool checkIntersection(const sf::Shape& shape1, const sf::Shape& shape2);

    // Objects
    std::vector<sf::CircleShape> treesVector;
    std::vector<sf::RectangleShape> rocksVector;

    // Constructor / destructor
    World(sf::Vector2f gameAreaSize, int numTrees, int numRocks);
    virtual ~World();

    // Render functions
    void render(sf::RenderTarget& target);


};