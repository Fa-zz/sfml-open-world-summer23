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
    while (treesVector.size() < Data::numTrees) {
        float x = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        float y = randomFloat(0+150.f, Data::gameWorldSizeY-150.f);
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

    while (fallenTreesVector.size() < Data::numFallenTrees) {
        float x = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        float y = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        sf::RectangleShape rectangle;

        int treeHorizOrVertChance = randomInt(1,3);

        switch(treeHorizOrVertChance) {
        case 1:
            rectangle.setSize(sf::Vector2f(
                400.f,
                100.f
            ));
            break;
        case 2:
            rectangle.setSize(sf::Vector2f(
                100.f,
                400.f
            ));
            break;
        }

        rectangle.setPosition(x, y);
        rectangle.setFillColor(CustomColors::treeBarkColor);

        bool intersects = std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingCircle) {
            return checkIntersection(rectangle, existingCircle);
        });

        if (!intersects)
        {
            fallenTreesVector.push_back(rectangle);
        }

    }
}

void World::generateRocks() {
    while (rocksVector.size() < Data::numRocks) {
        float x = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        float y = randomFloat(0+150.f, Data::gameWorldSizeY-150.f);
        sf::CircleShape rock;

        int rockBiglinessChance = randomInt(1,3);
        int rockColorChance = randomInt(1,7);

        switch(rockBiglinessChance) {
        case 1:
            rock.setRadius(
                randomFloat(10.f, 20.f)
                );
            break;
        case 2:
            rock.setRadius(
                randomFloat(20.f, 50.f)
                );
            break;
        }

        switch(rockColorChance) {
        case 1:
            rock.setFillColor(CustomColors::rockColor1);
            break;
        case 2:
            rock.setFillColor(CustomColors::rockColor2);
            break;
        case 3:
            rock.setFillColor(CustomColors::rockColor3);
            break;
        case 4:
            rock.setFillColor(CustomColors::rockColor4);
            break;
        case 5:
            rock.setFillColor(CustomColors::rockColor5);
            break;
        case 6:
            rock.setFillColor(CustomColors::rockColor6);
            break;
        default:
            rock.setFillColor(sf::Color::Black);
        }

        // rectangle.setSize(sf::Vector2f(rockWidth, rockHeight));
        rock.setPosition(x, y);

        bool intersects = std::any_of(rocksVector.begin(), rocksVector.end(), [&](const sf::CircleShape& existingRock) {
            return checkIntersection(rock, existingRock);
        });

        intersects = intersects || std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingCircle) {
            return checkIntersection(rock, existingCircle);
        });

        if (!intersects)
        {
            rocksVector.push_back(rock);
        }
    }
}

void World::generateMudPatches() {
    while (mudPatchesVector.size() < Data::numMudPatches) {
        float x = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        float y = randomFloat(0+150.f, Data::gameWorldSizeY-150.f);
        sf::RectangleShape mudPatch;

        mudPatch.setSize(sf::Vector2f(500, 500));
        mudPatch.setFillColor(CustomColors::mudColor);
        mudPatch.setOutlineColor(sf::Color::Black);
        mudPatch.setOutlineThickness(5.f);

        mudPatch.setPosition(x, y);

        bool intersects = std::any_of(mudPatchesVector.begin(), mudPatchesVector.end(), [&](const sf::RectangleShape& existingMud) {
            return checkIntersection(mudPatch, existingMud);
        });

        // intersects = intersects || std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingCircle) {
        //     return checkIntersection(mudPatch, existingCircle);
        // });

        if (!intersects)
        {
            std::cout << "mud patch pushed back, coords: " << mudPatch.getPosition().x << " " << mudPatch.getPosition().y << std::endl;
            mudPatchesVector.push_back(mudPatch);
        }
    }

}

void World::generateBushes() {
    while (bushesVector.size() < Data::numMudPatches) {
        float x = randomFloat(0+150.f, Data::gameWorldSizeX-150.f);
        float y = randomFloat(0+150.f, Data::gameWorldSizeY-150.f);
        sf::CircleShape bush(100.f, 8);

        bush.setFillColor(CustomColors::bushColor);
        bush.setPosition(x, y);

        bool intersects = std::any_of(bushesVector.begin(), bushesVector.end(), [&](const sf::CircleShape& existingBush) {
            return checkIntersection(bush, existingBush);
        });

        intersects = intersects || std::any_of(treesVector.begin(), treesVector.end(), [&](const sf::CircleShape& existingTree) {
            return checkIntersection(bush, existingTree);
        });

        intersects = intersects || std::any_of(fallenTreesVector.begin(), fallenTreesVector.end(), [&](const sf::RectangleShape& existingFallenTree) {
            return checkIntersection(bush, existingFallenTree);
        });

        intersects = intersects || std::any_of(mudPatchesVector.begin(), mudPatchesVector.end(), [&](const sf::RectangleShape& existingMudPatch) {
            return checkIntersection(bush, existingMudPatch);
        });


        if (!intersects)
        {
            bushesVector.push_back(bush);
        }
    }

}


// CONSTRUCTOR / DESTRUCTOR
World::World() {
    srand(time(0));
    generateTrees();
    generateRocks();
    generateMudPatches();
    generateBushes();
}

World::~World() {
    
}

void World::render(sf::RenderTarget& target) {
    for (auto iter = 0; iter < mudPatchesVector.size(); ++iter) {
        target.draw(mudPatchesVector[iter]);
    }
    for (auto iter = 0; iter < treesVector.size(); ++iter) {
        target.draw(treesVector[iter]);
    }
    for (auto iter = 0; iter < fallenTreesVector.size(); ++iter) {
        target.draw(fallenTreesVector[iter]);
    }
    for (auto iter = 0; iter < rocksVector.size(); ++iter) {
        target.draw(rocksVector[iter]);
    }
    for (auto iter = 0; iter < bushesVector.size(); ++iter) {
        target.draw(bushesVector[iter]);
    }

}