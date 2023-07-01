#pragma once

#include "World.hpp"
#include "GameUI.hpp"

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
    sf::Vector2f playerMidpoint;
    sf::Vector2f circlePosition;

    // Player collision vars
    sf::FloatRect playerNewBounds;
    sf::FloatRect collidingWith;

    // Mouse vars
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    bool mouseHeld;
    sf::CircleShape visibleToPlayer;

    // Window, view, time
    sf::RenderWindow* window;
    sf::View mainView;
    // float viewSpeed;
    sf::Clock clock;
    float currentTime;
    float timer;

    // Light
    candle::RadialLight* lightPtr;
    candle::LightingArea* fogPtr;

    // Player
    sf::CircleShape player;

    // Game UI
    GameUI* gameUIPtr;

    // World
    World* gameWorldPtr;

    FPS fps;

    // Init functions
    void initWindow();
    void initVars();
    void initLight();
    void generatePlayerPosition();
    void initPlayer();
    void initObjects();
    void initUI();
    void initView();

public:
    // CONSTRUCTOR/DESTRUCTOR
    Engine();
    virtual ~Engine();

    // Functions
    void run();

    // Update functions
    void pollEvents();
    void updateMousePos();
    void updateMouse();

    void playerOutOfBoundsAdjust();
    bool playerObjectCollision(sf::CircleShape& playerArg);
    void updatePlayer();

    void updateSanity();
    void updateUI();

    void update();

    // Render functions
    void renderUI(sf::RenderTarget& target);
    void renderObjects(sf::RenderTarget& target);
    void render();
};