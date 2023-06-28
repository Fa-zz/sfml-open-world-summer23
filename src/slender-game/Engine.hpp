#include <SFML/Graphics.hpp>

#include <iostream>

class Engine {
private:
    // Variables

    // Window view
    sf::RenderWindow* window;
    sf::View mainView;
    float viewSpeed;

    // Player, elems
    sf::RectangleShape player;
    sf::RectangleShape object;
    sf::RectangleShape UIElem;

    // Private functions
    void initWindow();
    void initObjects();
    void initPlayer();
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