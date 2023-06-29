#pragma once

#include "World.hpp"

#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"

class Engine {
private:
    // Game area variables
    sf::Vector2f gameAreaSize;
    sf::FloatRect* gameAreaBoundsPtr;

    // Player movement vars
    float playerMoveSpeed;
    sf::Vector2f playerMovement;
    sf::Vector2f playerNewPosition;

    // Player midpoint vars
    sf::Vector2f circlePosition;

    // Player collision vars
    sf::FloatRect playerNewBounds;
    sf::FloatRect collidingWith;

    // Window, view
    sf::RenderWindow* window;
    sf::View mainView;
    // float viewSpeed;

    // Light
    candle::RadialLight* lightPtr;
    candle::LightingArea* fogPtr;

    // Player, objects
    // sf::CircleShape newPlayer;
    sf::CircleShape player;
    // sf::RectangleShape object;
    sf::RectangleShape UIElem;

    // World
    World* gameWorldPtr;

    // Private functions
    void initWindow();
    void initVars();
    void initLight();
    void generatePlayerPosition();
    void initPlayer();
    void initObjects();
    void initView();

public:
    Engine();
    virtual ~Engine();

    // Functions
    void run();

    void pollEvents();
    void playerOutOfBoundsAdjust();
    bool playerObjectCollision(sf::CircleShape& playerArg);
    void updatePlayer();

    void update();
    void render();
};