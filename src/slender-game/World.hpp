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
    // Generate world functions
    void generateTrees();
    void generateRocks();
    void generateMudPatches();
    void generateBushes();
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
    std::vector<sf::RectangleShape> fallenTreesVector;
    std::vector<sf::CircleShape> rocksVector;
    std::vector<sf::RectangleShape> mudPatchesVector;
    std::vector<sf::CircleShape> bushesVector;

    // Constructor / destructor
    World();
    virtual ~World();

    // Render functions
    void render(sf::RenderTarget& target);


};