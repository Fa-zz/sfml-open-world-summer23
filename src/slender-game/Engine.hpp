#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Candle/RadialLight.hpp"
#include "Candle/LightingArea.hpp"

#include <vector>
#include <iostream>

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

    // Window, view
    sf::RenderWindow* window;
    sf::View mainView;
    // float viewSpeed;

    // Light
    candle::RadialLight* lightPtr;
    candle::LightingArea* fogPtr;

    // Player, objects
    sf::CircleShape player;
    sf::RectangleShape object;
    sf::RectangleShape UIElem;

    // Private functions
    void initWindow();
    void initVars();
    void initLight();
    void initPlayer();
    void initObjects();
    void initView();

public:
    Engine();
    virtual ~Engine();

    // Functions
    void run();

    void pollEvents();
    void updatePlayer();

    void update();
    void render();
};