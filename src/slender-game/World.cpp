#include "World.hpp"

// Helper functions
float World::randomFloat() {
    return (float)(rand()) / (float)(RAND_MAX);
}
 
int World::randomInt(int a, int b) {
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}
 
float World::randomFloat(int a, int b) {
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;
 
    return (float)randomInt(a, b) + randomFloat();
}

bool World::checkIntersection(const sf::Shape& shape1, const sf::Shape& shape2) {
    return shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
}

// Populate world
void World::generateTrees() {
    while (treeVector.size() < m_numTrees) {
        float x = randomFloat(0+150.f, m_gameAreaSize.x-150.f);
        float y = randomFloat(0+150.f, m_gameAreaSize.y-150.f);
        std::cout << "Tree vector size: " << treeVector.size() << " Tree x: " << x << " Tree y: " << y << std::endl;

        //TODO: Move all colors elsewhere.
        sf::Color treeBarkColor(37,21,11);
        sf::Color leafColor(58,95,11);

        sf::CircleShape circle(150.f);
        circle.setFillColor(treeBarkColor);
        circle.setOutlineThickness(20);
        circle.setOutlineColor(leafColor);
        circle.setPosition(x, y);

        bool intersects = std::any_of(treeVector.begin(), treeVector.end(), [&](const sf::CircleShape& existingCircle) {
            return checkIntersection(circle, existingCircle);
        });

        if (!intersects)
        {
            treeVector.push_back(circle);
        }

    }
}

// CONSTRUCTOR / DESTRUCTOR
World::World(sf::Vector2f gameAreaSize, int numTrees, int numRocks): 
    m_gameAreaSize(gameAreaSize), m_numTrees(numTrees), m_numRocks(numRocks) {
    srand(time(0));
    generateTrees();
}

World::~World() {
    
}