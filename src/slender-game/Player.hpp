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

    // Sanity, timers
    bool meditateActivated;
    int sanity;
    float sanityTimer, breathTimer;

    // Hiding, health
    bool hidingActivated;
    bool overHideable;
    int hideable;
    bool leftHiding;
    int health, breath, difference, maxBar;
    bool displayBreath;
    bool isBreathing;

    // Movement vars
    bool outOfBounds;
    bool statusStill, statusWalking, statusRunning;
    float playerSpeedModifier, playerMoveSpeed;
    sf::Vector2f playerMovement, playerNewPosition;

    // Flashlight
    bool flashlightOn;

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
    void updateBreathTimer(float currentTime);  // Called in Engine
    void updateSanityTimer(float currentTime);  // Called in Engine
    void updateBreath();
    void updateHiding();
    void updateSanity(bool isMeditating);
    void updateItem();
    void updatePlayer();

    // Getters
    sf::FloatRect getPlayerGlobalBounds();
    bool getActivity();
    bool getPlayerOutOfBounds();
    bool getMeditateActivated();
    std::array<bool, 2> getHiding(); // Returns hidingActivated and overHideable, in that order
    int getHideable();
    std::array<bool, 3> getStatus();
    int getSanity();
    sf::CircleShape getPlayer();
    bool getFlashlightOn();
    int getBreath();
    bool getDisplayBreath();
    int getHealth();

    // Getters - timers
    float getSanityTimer();
    float getBreathTimer();

    // Setters
    void setMeditateActivated(bool meditating);
    void setHidingActivated(bool hiding);
    void setFlashlightOn(bool newFlashlight);

};