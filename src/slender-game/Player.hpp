#pragma once

#include <iostream>
#include <cmath>

#include "World.hpp"
#include "Data.hpp"
#include "CustomColors.hpp"

class Player {
private:
    sf::CircleShape player;
    sf::Color playerSkinTone;

    World* m_gameWorldPtr;
    sf::FloatRect* m_gameAreaBoundsPtr;

    // Sanity, hiding
    bool meditateActivated, hidingActivated;
    bool overHideable;
    int hideable;

    // Movement vars
    bool outOfBounds;
    bool statusStill, statusWalking, statusRunning;
    float playerSpeedModifier, playerMoveSpeed;
    sf::Vector2f playerMovement, playerNewPosition;

    // Helper funcs
    bool playerObjectCollision(sf::CircleShape playerArg);
    void generatePlayerPosition();
    void modifySpeedIfObstacles();
    void updatePlayerMovement(float modifier);
    void playerOutOfBoundsAdjust();

    // Init funcs
    void initPlayer();
    void initVars();

public:
    // Constructor
    Player(World* gameWorldPtr, sf::FloatRect* gameAreaBoundsPtr);

    // Update
    void updatePlayer();

    // Getters
    bool getPlayerOutOfBounds();
};