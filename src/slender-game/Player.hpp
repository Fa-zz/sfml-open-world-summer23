#pragma once

#include <iostream>
#include <cmath>
#include <array>

#include "World.hpp"
#include "Data.hpp"
#include "CustomColors.hpp"

class Player {
private:
    sf::CircleShape player;
    sf::Color playerSkinTone;

    World* m_gameWorldPtr;
    sf::FloatRect* m_gameAreaBoundsPtr;

    // Sanity, timer
    bool meditateActivated;
    int sanity;
    float sanityTimer;

    // Hiding, health
    bool hidingActivated;
    bool overHideable;
    int hideable;
    int health;
    int difference;

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
    void updateSanityTimer(float currentTime);  // Called in Engine
    void updateSanity(bool isMeditating);
    void updatePlayer();

    // Getters
    sf::FloatRect getPlayerGlobalBounds();
    bool getActivity();
    bool getPlayerOutOfBounds();
    bool getMeditateActivated();
    std::array<bool, 2> getHiding(); // Returns hidingActivated and overHideable
    int getHideable();
    std::array<bool, 3> getStatus();
    int getSanity();
    sf::CircleShape getPlayer();

    // Getters - timers
    float getSanityTimer();

    // Setters
    void setMeditateActivated(bool meditating);

};