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
    while (treesVector.size() < m_numTrees) {
        float x = randomFloat(0+150.f, m_gameAreaSize.x-150.f);
        float y = randomFloat(0+150.f, m_gameAreaSize.y-150.f);
        std::cout << "Tree vector size: " << treesVector.size() << " Tree x: " << x << " Tree y: " << y << std::endl;

        //TODO: Randomize colors.
        //TODO: organize random generation more cleanly (all random values top of loop)
        float treeRadius = randomFloat(70.f, 110.f);
        int treeOutlineThickness = randomInt(20, 60);

        sf::CircleShape circle(treeRadius);
        circle.setFillColor(CustomColors::treeBarkColor);
        circle.setOutlineThickness(treeOutlineThickness);
        circle.setOutlineColor(CustomColors::leafColor);
        circle.setPosition(x, y);

        bool intersects = std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingCircle) {
            return checkIntersection(circle, existingCircle);
        });

        if (!intersects)
        {
            treesVector.push_back(circle);
        }

    }
}

void World::generateRocks() {
    while (rocksVector.size() < m_numRocks) {
        float x = randomFloat(0+150.f, m_gameAreaSize.x-150.f);
        float y = randomFloat(0+150.f, m_gameAreaSize.y-150.f);
        std::cout << "Rock vector size: " << rocksVector.size() << " Rock x: " << x << " Rock y: " << y << std::endl;
        sf::RectangleShape rectangle;

        int rockBiglinessChance = randomInt(1,4);
        int rockColorChance = randomInt(1,7);

        switch(rockBiglinessChance) {
        case 1:
            rectangle.setSize(sf::Vector2f(
                randomFloat(30.f, 60.f),
                randomFloat(30.f, 40.f)
            ));
            break;
        case 2:
            rectangle.setSize(sf::Vector2f(
                randomFloat(60.f, 100.f),
                randomFloat(50.f, 70.f)
            ));
            break;
        case 3:
            rectangle.setSize(sf::Vector2f(
                randomFloat(20.f, 40.f),
                randomFloat(30.f, 40.f)
            ));
            break;
        }

        switch(rockColorChance) {
        case 1:
            rectangle.setFillColor(CustomColors::rockColor1);
            break;
        case 2:
            rectangle.setFillColor(CustomColors::rockColor2);
            break;
        case 3:
            rectangle.setFillColor(CustomColors::rockColor3);
            break;
        case 4:
            rectangle.setFillColor(CustomColors::rockColor4);
            break;
        case 5:
            rectangle.setFillColor(CustomColors::rockColor5);
            break;
        case 6:
            rectangle.setFillColor(CustomColors::rockColor6);
            break;
        default:
            rectangle.setFillColor(sf::Color::Black);
        }

        // rectangle.setSize(sf::Vector2f(rockWidth, rockHeight));
        rectangle.setPosition(x, y);

        bool intersects = std::any_of(rocksVector.begin(), rocksVector.end(), [&](const sf::RectangleShape& existingRectangle) {
            return checkIntersection(rectangle, existingRectangle);
        });

        intersects = intersects || std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingCircle) {
            return checkIntersection(rectangle, existingCircle);
        });

        if (!intersects)
        {
            rocksVector.push_back(rectangle);
        }
    }
}

// CONSTRUCTOR / DESTRUCTOR
World::World(sf::Vector2f gameAreaSize, int numTrees, int numRocks): 
    m_gameAreaSize(gameAreaSize), m_numTrees(numTrees), m_numRocks(numRocks) {
    srand(time(0));
    generateTrees();
    generateRocks();
}

World::~World() {
    
}

void World::render(sf::RenderTarget& target) {
    for (auto iter = 0; iter < treesVector.size(); ++iter) {
        target.draw(treesVector[iter]);
    }
    for (auto iter = 0; iter < rocksVector.size(); ++iter) {
        target.draw(rocksVector[iter]);
    }

}