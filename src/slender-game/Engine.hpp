#pragma once

#include "World.hpp"
#include "GameUI.hpp"
#include "GameAudio.hpp"

#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"

class Engine {
private:
    // Game area variables
    sf::Vector2f gameAreaSize;
    sf::FloatRect* gameAreaBoundsPtr;

    // Player movement vars
    float playerSpeedModifier;
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
    float sanityTimer;
    float breathTimer;
    float flashlightBatteryTimer;
    sf::Time getElapsed;
    float totalTime;
    FPS fps;

    // Light, battery
    candle::RadialLight* lightPtr;
    candle::LightingArea* fogPtr1;
    candle::LightingArea* fogPtr2;
    float currentLightRange;
    int flashlightBattery;

    // Player
    sf::CircleShape player;
    sf::Color playerSkinTone;

    // Notes and Monster
    int notesFound;
    bool firstNoteFound, inAppearance, appearanceLogMessage;
    bool playAppearanceMusic, playGhostlyWhispers;
    float nextAppearanceTimer, appearanceHideTimer;
    int appearanceHappensAt;
    bool checkedInFound, inFound;

    // Game UI
    GameUI* UIPtr;
    std::vector<std::string> logMessages;
    float logTimer;

    // World
    World* gameWorldPtr;

    // Audio
    GameAudio* audioPtr;
    bool clickedFlashlight;

    // Controls
    bool meditateActivated;
    bool meditateButtonHeld;
    bool flashlightOn;
    bool overHideable;
    int hideable;               // Where 1 is bush, 2 is mud
    bool overRock;
    bool hidingActivated;
    bool isBreathing;
    bool leftHiding;
    bool statusRunning, statusWalking, statusStill;
    bool outOfBreath;

    bool overItem;
    bool useItem;
    int highlightedIter;
    std::string itemType;

    // Init functions
    void initWindow();
    void initVars();
    void initLight();
    void generatePlayerPosition();
    void initPlayer();
    void initObjects();
    void initUI();
    void initView();
    void initAudio();

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

    void playerActionsMeditate();
    void playerOutOfBoundsAdjust();
    bool playerObjectCollision(sf::CircleShape& playerArg);
    void updateItem();
    void modifySpeedIfObstacles();
    void updatePlayerMovement(float modifier);

    void updateSanity(bool isMeditating);
    void handleBreath();
    void updateHiding(bool hidingActivated, bool overHideable, int hideable);
    void updateUIActivityLevel(bool statusStill, bool statusWalking, bool statusRunning);
    void updatePlayer();
    void updateLog();
    void updateUI();
    void updateLight();
    void updateAudio();

    void updateMonster();

    void update();

    // Render functions
    void renderUI(sf::RenderTarget& target);
    void renderObjects(sf::RenderTarget& target);
    void render();
};